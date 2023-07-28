##client
##签名者A
from SM2ENC import SM2
from ecpy.curves     import Curve,Point
from ecpy.keys       import ECPublicKey, ECPrivateKey
from ecpy.ecdsa      import ECDSA
from ecpy            import ecrand
from ecpy.formatters  import decode_sig,encode_sig
import hashlib
import socket
import json
import time

def serialize_dict(data):
    return json.dumps(data).encode('utf-8')

def deserialize_dict(data):
    return json.loads(data.decode('utf-8'))


start=time.time()



S=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
HOST=socket.gethostname()
PORT=8080
S.connect((HOST,PORT))
while True:
    cv     = Curve.get_curve('secp256k1')
    n=cv.order
    G=cv.generator

    start=time.time()
    data=S.recv(1024)
    message=deserialize_dict(data)
    TS=cv.decode_point(message['data'])
    
    d1=ecrand.rnd(n-1)
    P=pow(d1,-1,n)*TS-G
    pu_key = ECPublicKey(P)

    encryptor=SM2("BTUPLE")
    message=b"hello"
    #print("要加密的消息是：",message)
    message_bit= ''.join(format(byte, '08b') for byte in message)
    #print("其对应的比特串是： ",message_bit)
    cipher=encryptor.encrypt(message_bit,pu_key)
   # print(cipher)
    C1_bit=cipher[0][0:cipher[1]]
    x1_bit=C1_bit[8:8+cipher[4]]
    y1_bit=C1_bit[8+cipher[4]:]
    x1=int(x1_bit,2)
    y1=int(y1_bit,2)
    C1=Point(x1,y1,cv)
    #print("C1",C1)
    C2_bit=cipher[0][(cipher[1]+cipher[3]):]
    ##print(C2_bit)
    
    
    T1=(pow(d1,-1,n)*C1)
    T1_list=cv.encode_point(T1)   
    S.send(serialize_dict({'data':T1_list,'num':0}))
        
    data=S.recv(1024)
    message=deserialize_dict(data)
    T2=cv.decode_point(message['data'])

    T3=T2-C1
    #print("KP",T3)

    
    x2=T3.x
    y2=T3.y
    x2_bit=bin(x2)[2:]
    #print("2b",x2_bit)
    y2_bit=bin(y2)[2:]
   # print("3b",y2_bit)
    t=encryptor.KDF(x2_bit+y2_bit,cipher[-1])
    #print(t)

    M=int(t,2)^int(C2_bit,2)
    M_bit=bin(M)
    dudu=int(M_bit,2)
    num_byte = (dudu.bit_length() + 7) // 8
    M_byte = dudu.to_bytes(num_byte, 'big')
    print("解密时间为：",time.time()-start)
    print("解密结果是：",M_byte)
    stop = input("Do you want to stop? (y/n): ").strip().lower()
    if stop == 'y':
        S.send(serialize_dict({'num': -1}))
        break

S.close()

    
