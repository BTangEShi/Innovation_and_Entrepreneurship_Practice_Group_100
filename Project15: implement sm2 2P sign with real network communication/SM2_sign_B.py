##server
##签名者B
from SM2ENC import SM2
from ecpy.curves     import Curve,Point
from ecpy.keys       import ECPublicKey, ECPrivateKey
from ecpy.ecdsa      import ECDSA
from ecpy            import ecrand
from ecpy.formatters  import decode_sig,encode_sig
import hashlib
import socket
import json

def serialize_dict(data):
    return json.dumps(data).encode('utf-8')

def deserialize_dict(data):
    return json.loads(data.decode('utf-8'))
cv     = Curve.get_curve('secp256k1')

pu_key = ECPublicKey(Point(0x65d5b8bf9ab1801c9f168d4815994ad35f1dcb6ae6c7a1a303966b677b813b00,
0xe6b865e529b8ecbf71cf966e900477d49ced5846d7662dd2dd11ccd55c0aff7f,cv))

pv_key = ECPrivateKey(0xfb26a4e75eec75544c0f44e937dcf5ee6355c7176600b9688c667e5c283b43c5,cv)
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)

n=cv.order
G=cv.generator


HOST=socket.gethostname()
PORT=8080
s.bind((HOST,PORT))
print ('Server start at: %s:%s' %(HOST, PORT))
print ('wait for connection...')
s.listen(1)
while True:
    conn,addr=s.accept()
    print("Connected by",addr)
    while True:
        data=conn.recv(1024)
        message=deserialize_dict(data)
        if(message['num']==0):
            P1=cv.decode_point(message['data1'])
            d2=ecrand.rnd(n-1)
            d2_inv=pow(d2,-1,n)
            P=d2_inv*P1-G
            print("Public key: ",P)
        elif(message['num']==1):
            Q1=cv.decode_point(message['data1'])
            e=message['data2']
            e_int=int.from_bytes(e.encode())
            k2=ecrand.rnd(n-1)
            Q2=k2*G
            k3=ecrand.rnd(n-1)
            Q4=k3*Q1+Q2
            x1=Q4.x
            y1=Q4.y
            r=(x1+e_int)%n
            s2=(d2*k3)%n
            s3=(d2*(r+k2))%n
            conn.sendall(serialize_dict({'data1':r,'data2':s2,'data3':s3}))
            s.close()
        elif(message['num']==-1):
             break
    conn.close()
    break
s.close()
            
            
            
        
        
    
    
    
    
