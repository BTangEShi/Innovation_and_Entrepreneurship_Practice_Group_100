from ecpy.curves     import Curve,Point
from ecpy.keys       import ECPublicKey, ECPrivateKey
from ecpy.ecdsa      import ECDSA
from ecpy            import ecrand
from ecpy.formatters  import decode_sig,encode_sig
import hashlib

class SM2:
    
    def __init__(self,fmt="BTUPLE"):
        self.maxtries=10
        self.fmt=fmt
        pass
    def top(self,x,y):
        if (x/y ==x//y):
            return x//y
        else:
            return (x//y)+1
    def KDF(self,Z,klen):
        ct=0x00000001
        K=""
        H=[0]*(self.top(klen,256)+1)
        for i in range(1,self.top(klen,256)+1):
            formatted_str = "0x{:08x}".format(ct)
            H[i]=hashlib.sha256((Z+formatted_str[2:]).encode()).digest()
            print(H[i])
            H[i] = ''.join(format(byte, '08b') for byte in H[i])
            print(H[i])
            ct+=1
        if(klen//256 !=klen/256):
            bit_num=klen-256*(klen//256)
            H[self.top(klen,256)]=H[self.top(klen,256)][0:bit_num]
        for i in range(1,self.top(klen,256)+1):
            K+=H[i]
        return K   
        
        
    def encrypt(self,msg,pu_key):
        curve = pu_key.curve
        n     = curve.order
        G     = curve.generator
        for i in range(1,self.maxtries):
            k=ecrand.rnd(n-1)
            encode_msg=self._do_encrypt_(msg,pu_key,k)
            if encode_msg:
                return encode_msg
        return None
    def _do_encrypt_(self,msg,pu_key,k):
        curve = pu_key.curve
        n     = curve.order
        G     = curve.generator
        C1=k*G
        C1_bit='00000100'+bin(C1.x)[2:]+bin(C1.y)[2:]
        S=k*pu_key.W
        x2=S.x
        x2_bit=bin(x2)[2:]
        y2=S.y
        y2_bit=bin(y2)[2:]
        t=self.KDF(x2_bit+y2_bit,len(msg))
        C2=int(msg,2)^int(t,2)
        print(C2)
        C2_bit=bin(C2)[2:]
        C3=hashlib.sha256((x2_bit+msg+y2_bit).encode()).digest()
        C3_bit= ''.join(format(byte, '08b') for byte in C3)
        return (C1_bit+C3_bit+C2_bit,len(C1_bit),len(C2_bit),len(C3_bit),
                len(bin(C1.x)[2:]),len(bin(C1.y)[2:]))
        
    def decrypt(self,cipher,pv_key):
        curve=pv_key.curve
        n=curve.order
        G=curve.generator
        d=pv_key.d
        ##取出比特串C1
        C1_bit=cipher[0][0:cipher[1]]##字符串拼接问题
        x1=C1_bit[8:8+cipher[3]]
        y1=C1_bit[8+cipher[3]:]
        C1=Point(x,y,curve)
        if(C1,curve==False):
            print("C1不满足椭圆方程")
            return
        X=d*C1
        x2=X.x
        y2=X.y
        x2_bit=bin(x2)[2:]
        y2_bit=bin(y2)[2:]
        t=self.KDF(x2_bit+y2_bit,cipher[1])
        ##取出比特串C
        C3_bit=cipher[0][cipher[1]:(cipher[1]+cipher[3])]
        ##计算明文
        M=t^C3_bit
        return M
        
        
    def sign(self,msg,Z,pv_key):
        order=pv_key.curve.order
        for i in range(1,self.maxtries):
            k=ecrand.rnd(order)
            sig=self._do_sign_(msg,Z,pv_key,k)
            if sig:
                return sig
        return None
    def _do_sign_(self,msg,Z,pv_key,k):
        if (pv_key.curve == None):
            raise ECPyException('private key haz no curve')
        curve=pv_key.curve
        n=curve.order
        G=curve.generator
        k=k%n
        e = hashlib.sha256(Z+msg).digest()
        e_int = int.from_bytes(e)
        P=k*G
        r = (e_int + P.x) % n
        if(r==0 or r+k==n):
            return None
        d = pv_key.d
        x = pow((1 + d), -1, n)
        s = (x * (k - r * d)) % n
        if(s==0):
            return None
        sign=encode_sig(r,s,self.fmt)
        return sign
    def verify(self,msg,Z,sig,pu_key):
        curve = pu_key.curve
        n     = curve.order
        G     = curve.generator

        r,s = decode_sig(sig, self.fmt)
        if (r == None or r > n or s > n     ) :
            return False
        
        e = hashlib.sha256(Z+msg).digest()
        e_int = int.from_bytes(e)
        t = (r + s) % n
        P = s * G + t * pu_key.W
        R = (e_int + P.x) % n
        return R==r
##预计算

if __name__ == "__main__":
    try:
        ### SM2
        cv     = Curve.get_curve('secp256k1')
        pu_key = ECPublicKey(Point(0x65d5b8bf9ab1801c9f168d4815994ad35f1dcb6ae6c7a1a303966b677b813b00,
                                   
                                   0xe6b865e529b8ecbf71cf966e900477d49ced5846d7662dd2dd11ccd55c0aff7f,
                                   cv))
        pv_key = ECPrivateKey(0xfb26a4e75eec75544c0f44e937dcf5ee6355c7176600b9688c667e5c283b43c5,
                              cv)
        print("椭圆曲线是：",cv)
        ID = b"TangShi"
        entlen = len(ID) * 8
        ENTL = entlen.to_bytes(2, 'big')
        Z = hashlib.sha256(ENTL + ID + bin(cv.a)[2:].encode() + bin(cv.b)[2:].encode()
        + bin(cv.generator.x)[2:].encode()+ bin(cv.generator.y)[2:].encode() +
        bin((pv_key.d * cv.generator).x)[2:].encode() + bin((pv_key.d * cv.generator).y)[2:].encode()).digest()
        
        signer=SM2()
        ID = b"TangShi"
        entlen = len(ID) * 8
        ENTL = entlen.to_bytes(2, 'big')
        Z = hashlib.sha256(ENTL + ID + bin(cv.a)[2:].encode() + bin(cv.b)[2:].encode() + bin(cv.generator.x)[2:].encode() + bin(cv.generator.y)[2:].encode() + bin((pv_key.d * cv.generator).x)[2:].encode() + bin((pv_key.d * cv.generator).y)[2:].encode()).digest()
        message=b"Hello ts"
        print("消息是：",message)
        sig=signer.sign(message,Z,pv_key)
        print("签名是： ",sig)
        if(signer.verify(message,Z,sig,pu_key)==True):
            print("签名验证成功")
        else:
            print("签名验证失败")
    finally:
        pass


