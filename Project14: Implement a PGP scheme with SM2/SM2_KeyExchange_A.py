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
import math
def serialize_dict(data):
    return json.dumps(data).encode('utf-8')

def deserialize_dict(data):
    return json.loads(data.decode('utf-8'))





S=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
HOST=socket.gethostname()
PORT=8080
S.connect((HOST,PORT))
while True:
    cv     = Curve.get_curve('secp256k1')
    n=cv.order
    G=cv.generator
    pv_keyA = ECPrivateKey(0xfb26a4e75eec75544c0f44e937dcf5ee6355c7176600b9688c667e5c283b43c5,
                              cv)
    pu_keyA=pv_keyA.get_public_key()
    print("A的公钥是:",pu_keyA.W)
    dA=pv_keyA.d
    rA=ecrand.rnd(n-1)
    RA=rA*G
    S.send(serialize_dict({"data":cv.encode_point(RA),"keyx":pu_keyA.W.x,"keyy":pu_keyA.W.y}))
    x1=RA.x
    y1=RA.y
    w=math.ceil(math.ceil(math.log(n,2))/2)-1
    x1_=pow(2,w)+(x1&(pow(2,w)-1))
    tA=(dA+x1_*rA)%n
        
    data=S.recv(1024)
    message=deserialize_dict(data)
    RB=cv.decode_point(message['data'])
    print("RB",RB)
    pu_keyB=Point(message["keyx"],message["keyy"],cv)
    print("B的公钥是:",pu_keyB)
    if(cv.is_on_curve(RB)==False):
            print("RB不满足椭圆方程")
            break
    x2=RB.x
    y2=RB.y
    x2_=pow(2,w)+(x2&(pow(2,w)-1))
    
    U=tA*(pu_keyB+x2_*RB)
    
    print("U",U)
    xU=U.x
    yU=U.y
    encryptor=SM2("BTUPLE")
    KA=encryptor.KDF(bin(xU)[2:]+bin(yU)[2:],128)
    S1=hashlib.sha256((bin(xU)[2:]+bin(yU)[2:]).encode()).hexdigest()
    print("S1",S1)
    data=S.recv(1024)
    message=deserialize_dict(data)
    SB=(message['data'])
    if(S1==SB):
        print("密钥协商成功")
    else:
        print("密钥协商失败")

   

   
   
    stop = input("Do you want to stop? (y/n): ").strip().lower()
    if stop == 'y':
        S.send(serialize_dict({'num': -1}))
        break

S.close()

    
