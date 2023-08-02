from ecpy.curves     import Curve,Point
from ecpy.keys       import ECPublicKey, ECPrivateKey
from ecpy            import ecrand
from ecpy.formatters  import decode_sig,encode_sig
import hashlib
cv     = Curve.get_curve('secp256k1')
pu_key = ECPublicKey(Point(0x65d5b8bf9ab1801c9f168d4815994ad35f1dcb6ae6c7a1a303966b677b813b00,
0xe6b865e529b8ecbf71cf966e900477d49ced5846d7662dd2dd11ccd55c0aff7f,cv))
P=pu_key.W
pv_key = ECPrivateKey(0xfb26a4e75eec75544c0f44e937dcf5ee6355c7176600b9688c667e5c283b43c5,cv)
n=cv.order
G=cv.generator

def sign(msg, pv_key):
        """ Signs a message hash.

        Args:
            msg (bytes)                    : the message hash to sign
            pv_key (ecpy.keys.ECPrivateKey): key to use for signing
        """
        order = pv_key.curve.order
        for i in range(1,10):
            k = ecrand.rnd(order)
            sig = _do_sign(msg, pv_key,k)
            if sig:
                return sig
        return None
def _do_sign(msg,pv_key,k):
        if (pv_key.curve == None):
            raise ECPyException('private key haz no curve')
        curve = pv_key.curve
        n = curve.order
        G = curve.generator
        k = k%n

        msg = int.from_bytes(msg, 'big')
        
        Q = G*k
        kinv = pow(k,n-2,n)
        r = Q.x % n
        if r == 0:
            return None

        s = (kinv*(msg+pv_key.d*r)) %n
        if s == 0:
            return None
        
        sig = encode_sig(r,s,"BTUPLE")
        return sig
    
def verify(msg,sig,pu_key):
        curve = pu_key.curve
        n     = curve.order
        G     = curve.generator

        r,s = decode_sig(sig, "BTUPLE")
        if (r == None or
            r > n     or
            s > n     ) :
            return False

        h = int.from_bytes(msg,'big')
        c   = pow(s, n-2, n)
        u1  = (h*c)%n
        u2  = (r*c)%n
        u1G = u1*G
        u2Q = u2*pu_key.W
        GQ  =  u1G+u2Q
        x   = GQ.x % n

        return x == r
message=b"hello world"
message_hash=hashlib.sha256(message).digest()
sig=sign(message_hash,pv_key)
r,s = decode_sig(sig, "BTUPLE")
##开始构造
u=3
v=5
R_=u*G+v*P
x_=R_.x
y_=R_.y
r_=x_%n
print("伪造的r:",r_)
e_=(r_*u*pow(v,-1,n))%n
print("伪造的e:",e_)

s_=(r_*pow(v,-1,n))%n
print("伪造的s：",s_)
sig_fake=encode_sig(r_,s_,"BTUPLE")
hash_fake=e_.to_bytes((e_.bit_length() + 7) // 8, 'big')
if(verify(hash_fake,sig_fake,pu_key)==True):
    print("succeed to forge a signature to pretend that you are Satoshi")
else:
    print("fail to forge a signature to pretend that you are Satoshi")
