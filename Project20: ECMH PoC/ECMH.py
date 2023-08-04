from ecpy.curves     import Curve,Point
from ecpy.keys       import ECPublicKey, ECPrivateKey
from ecpy.ecdsa      import ECDSA
from ecpy            import ecrand
from ecpy.formatters  import decode_sig,encode_sig
import hashlib
import time
cv     = Curve.get_curve('secp256k1')
pu_key = ECPublicKey(Point(0x65d5b8bf9ab1801c9f168d4815994ad35f1dcb6ae6c7a1a303966b677b813b00,
                                   0xe6b865e529b8ecbf71cf966e900477d49ced5846d7662dd2dd11ccd55c0aff7f,
                                   cv))
pv_key = ECPrivateKey(0xfb26a4e75eec75544c0f44e937dcf5ee6355c7176600b9688c667e5c283b43c5,
                              cv)
n     = cv.order
G     = cv.generator
p     =cv.field
def Hash(msg):
    x = int(hashlib.sha256(msg.encode()).hexdigest(), 16) % p
    while True:
        temp = (x ** 3 +7)%p
        y = pow(temp, (p + 1) // 4, p)
        P=Point(x,y,cv,False)
        if(cv.is_on_curve(P)==True):
            return P
            break
        else:
            x+=1
        
    
def setHash(s):
    P = Hash(s[0])
    for msg in s[1:]:
        P += Hash(msg)
    return P


s1 = ['test1']
s2 = ['test2']
s3 = ['test3']
s12 = s1 + s2
s = ['test1', 'test2', 'test3']
print(setHash(s))
print(setHash(s1 + s2 + s3))
print(setHash(s12 + s3))
         
