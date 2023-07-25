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
            H[i] = ''.join(format(byte, '08b') for byte in H[i])
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
        ##print(C1_bit)
        S=k*pu_key.W
        x2=S.x
        x2_bit=bin(x2)[2:]
        y2=S.y
        y2_bit=bin(y2)[2:]
        t=self.KDF(x2_bit+y2_bit,len(msg))
        print("x2_bit+y2_bit",x2_bit+y2_bit)
        print("length: ",len(msg))
        print("t: ",t)
        C2=int(msg,2)^int(t,2)
        print("C2: ",C2)
        C2_bit=bin(C2)[2:]
        C3=hashlib.sha256((x2_bit+msg+y2_bit).encode()).digest()
        C3_bit= ''.join(format(byte, '08b') for byte in C3)
        return (C1_bit+C3_bit+C2_bit,len(C1_bit),len(C2_bit),len(C3_bit),
                len(bin(C1.x)[2:]),len(bin(C1.y)[2:]),len(msg))
        
    def decrypt(self,cipher,pv_key):
        curve=pv_key.curve
        n=curve.order
        G=curve.generator
        d=pv_key.d
        ##取出比特串C1
        C1_bit=cipher[0][0:cipher[1]]##字符串拼接问题
        x1_bit=C1_bit[8:8+cipher[4]]
        y1_bit=C1_bit[8+cipher[4]:]
        x1=int(x1_bit,2)
        y1=int(y1_bit,2)
        C1=Point(x1,y1,curve)
        if(curve.is_on_curve(C1)==False):
            print("C1不满足椭圆方程")
            return
        X=d*C1
        x2=X.x
        y2=X.y
        x2_bit=bin(x2)[2:]
        y2_bit=bin(y2)[2:]
        t=self.KDF(x2_bit+y2_bit,cipher[-1])
        print("x2_bit+y2_bit",x2_bit+y2_bit)
        print("length: ",cipher[-1])
        print("t: ",t)
        ##取出比特串C2
        C2_bit=cipher[0][(cipher[1]+cipher[3]):]
        print("C2: ",int(C2_bit,2))
        ##计算明文
        M=int(t,2)^int(C2_bit,2)
        M_bit=bin(M)
        dudu=int(M_bit,2)
        num_byte = (dudu.bit_length() + 7) // 8
        M_byte = dudu.to_bytes(num_byte, 'big')
        return (M,M_bit,M_byte)
        
        
    def sign(self,msg,pv_key):
        order=pv_key.curve.order
        for i in range(1,self.maxtries):
            k=ecrand.rnd(order)
            sig=self._do_sign_(msg,pv_key,k)
            if sig:
                return sig
        return None
    def _do_sign_(self,msg,pv_key,k):
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
    def verify(self,msg,sig,pu_key):
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
        encryptor=SM2()
        message=b"hello"
        print("要加密的消息是：",message)
        message_bit= ''.join(format(byte, '08b') for byte in message)
        print("其对应的比特串是： ",message_bit)
        cipher=encryptor.encrypt(message_bit,pu_key)
        print("密文是： ",cipher[0])
        overcome=encryptor.decrypt(cipher,pv_key)
        print("恢复后的明文是： ",overcome)     
    finally:
        pass

