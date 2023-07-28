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
        d2=ecrand.rnd(n-1)
        TS=cv.encode_point(pow(d2,-1,n)*G)
        conn.send(serialize_dict({"data":TS}))
        data=conn.recv(1024)
        message=deserialize_dict(data)
        if(message['num']==0):
            T1=cv.decode_point(message['data'])
            T2=pow(d2,-1,n)*T1
            T2_list=cv.encode_point(T2) 
            conn.send(serialize_dict({"data":T2_list}))
        elif(message['num']==-1):
             break
    conn.close()
    break
s.close()
            
            
            
        
        
    
    
    
    
