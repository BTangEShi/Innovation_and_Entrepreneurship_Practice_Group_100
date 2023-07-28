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
cv     = Curve.get_curve('secp256k1')
pu_key = ECPublicKey(Point(0x65d5b8bf9ab1801c9f168d4815994ad35f1dcb6ae6c7a1a303966b677b813b00,
0xe6b865e529b8ecbf71cf966e900477d49ced5846d7662dd2dd11ccd55c0aff7f,cv))

pv_key = ECPrivateKey(0xfb26a4e75eec75544c0f44e937dcf5ee6355c7176600b9688c667e5c283b43c5,cv)
n=cv.order
G=cv.generator

S=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
HOST=socket.gethostname()
PORT=8080
S.connect((HOST,PORT))
while True:
    d1=ecrand.rnd(n-1)
    d1_inv=pow(d1,-1,n)
    P1=d1_inv*G
    P1_list=cv.encode_point(P1)
    S.send(serialize_dict({'num':0,'data1':P1_list}))
    M=input("please input the message you will sign:")
    Z="AB"
    M_=Z+M
    e= hashlib.sha256(M_.encode()).hexdigest()
    k1=ecrand.rnd(n-1)
    Q1=k1*G
    Q1_list=cv.encode_point(Q1)
    S.send(serialize_dict({'num':1,'data1':Q1_list,'data2':e}))

    data=S.recv(1024)
    message=deserialize_dict(data)
    r=message['data1']
    s2=message['data2']
    s3=message['data3']
    s=((d1*k1)*s2+d1*s3-r)%n
    print("signature:")
    print('r',r)
    print('s',s)
    end=time.time()
    print(end-start)
    stop = input("Do you want to stop? (y/n): ").strip().lower()
    if stop == 'y':
        S.send(serialize_dict({'num': -1}))
        break

S.close()

    
