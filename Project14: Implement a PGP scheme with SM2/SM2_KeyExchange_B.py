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
import time
import math
def serialize_dict(data):
    return json.dumps(data).encode('utf-8')

def deserialize_dict(data):
    return json.loads(data.decode('utf-8'))
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
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
        cv     = Curve.get_curve('secp256k1')
        n=cv.order
        G=cv.generator
        pv_keyB = ECPrivateKey(0xeb26a4e75eec75544c0f44e937dcf5ee6355c7176600b9688c667e5c283b43c5,
                              cv)
        pu_keyB=pv_keyB.get_public_key()
        print("B的公钥是:",pu_keyB.W)
        dB=pv_keyB.d
        rB=ecrand.rnd(n-1)
        RB=rB*G
        print("RB",RB)
        conn.send(serialize_dict({"data":cv.encode_point(RB),"keyx":pu_keyB.W.x,"keyy":pu_keyB.W.y}))
        x2=RB.x
        y2=RB.y
        w=math.ceil(math.ceil(math.log(n,2))/2)-1
        x2_=pow(2,w)+(x2&(pow(2,w)-1))
        tB=(dB+x2_*rB)%n
        
        data=conn.recv(1024)
        message=deserialize_dict(data)
        pu_keyA=Point(message["keyx"],message["keyy"],cv)
        print("A的公钥是:",pu_keyA)
        RA=cv.decode_point(message['data'])
        print("RA",RA)
        if(cv.is_on_curve(RA)==False):
            print("RA不满足椭圆方程")
            break
        x1=RA.x
        y1=RA.y
        x1_=pow(2,w)+(x1&(pow(2,w)-1))
    
        V=tB*(pu_keyA+x1_*RA)

        
        print("V",V)
        xV=V.x
        yV=V.y
        encryptor=SM2("BTUPLE")
        KB=encryptor.KDF(bin(xV)[2:]+bin(yV)[2:],128)
        SB=hashlib.sha256((bin(xV)[2:]+bin(yV)[2:]).encode()).hexdigest()
        print("SB",SB)
        conn.send(serialize_dict({"data":SB}))
        break
    conn.close()
    break
s.close()
            
            
            
        
        
    
    
    
    
