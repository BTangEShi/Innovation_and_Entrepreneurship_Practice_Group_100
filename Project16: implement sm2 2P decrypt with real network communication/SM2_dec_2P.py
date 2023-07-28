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

cv     = Curve.get_curve('secp256k1')
n=cv.order
G=cv.generator

start=time.time()

d2=ecrand.rnd(n-1)
TS=(pow(d2,-1,n)*G)
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
T2=pow(d2,-1,n)*T1
T3=T2-C1
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
