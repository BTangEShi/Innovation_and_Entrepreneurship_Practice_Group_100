import random
import hashlib
import time
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.backends import default_backend

# 椭圆曲线参数(secp256k1)
p = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F
n = 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141
A = 0x0000000000000000000000000000000000000000000000000000000000000000
B = 0x0000000000000000000000000000000000000000000000000000000000000007
Gx = 0x79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798
Gy = 0x483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8

#计算a在模m下的逆元素
def inverse_mod(a, m):
    return pow(a, -1, m)


def calculate_y_coordinate(x):
    # 计算 x^3 + ax + b
    right_side = (x**3 + A*x + B) % p

    # 求解 y = ±√(x^3 + ax + b)
    y_square = right_side % p
    y = pow(y_square, (p + 1) // 4, p)

    return y


#椭圆曲线上点的加法P和Q是要相加的两个点，p是素数p，a是曲线参数A返回相加后的点R
def point_addition(P, Q, p, a):
    if P is None:
        return Q
    if Q is None:
        return P
    if P[0] == Q[0] and P[1] != Q[1]:
        return None
    if P != Q:
        lam = ((Q[1] - P[1]) * inverse_mod(Q[0] - P[0], p)) % p
    else:
        lam = ((3 * P[0]**2 + a) * inverse_mod(2 * P[1], p)) % p
    x = (lam**2 - P[0] - Q[0]) % p
    y = (lam * (P[0] - x) - P[1]) % p
    return (x, y)

def point_subtraction(P, Q, p, a):
    # 计算点 Q 的负元素 -Q
    if Q is None:
        return P
    Q_negative = (Q[0], (-Q[1]) % p)

    # 使用点加法函数计算 P - Q
    result = point_addition(P, Q_negative, p, a)

    return result
#对点P进行k倍的标量乘法k: 标量（整数）P: 要乘的点（点的坐标(x, y)）
#p: 素数p a: 曲线参数A  返回：标量乘法后的点坐标
def point_multiplication(k, P, p, a):
    R = None
    for i in range(k.bit_length()):
        if k & (1 << i):
            R = point_addition(R, P, p, a)
        P = point_addition(P, P, p, a)
    return R

#判断点 (x, y) 是否在椭圆曲线 y^2 = x^3 + ax + b 上
def is_point_on_elliptic_curve(x, y):
    left_side = (y**2) % p
    right_side = (x**3 + A*x + B) % p
    return left_side == right_side

#将sm3作为hash函数
def sm3(data):
    digest = hashes.Hash(hashes.SM3(), backend=default_backend())
    digest.update(data)
    result = digest.finalize()
    return result

#随机生成一对公钥和私钥  返回：(private_key, public_key) 公钥和私钥的组合
def generate_key_pair():
    private_key = random.randrange(1, n)
    public_key = point_multiplication(private_key, (Gx, Gy), p, A)
    return private_key, public_key


#Schnorr Signature签名函数
def sign_message(message,private_key):
    
    # 生成随机数k
    k = 1
    while k == 1:
        k = random.randrange(1, n)
    x, y = point_multiplication(k, (Gx, Gy), p, A)
    # 将消息哈希为一个大整数
    e = int.from_bytes(sm3((hex(x)[2:]+hex(y)[2:]+message).encode('utf-8')), byteorder='big')

    #签署消息
    s = (k + e * private_key) % n
    
    return ((x,y), s)

#签名验证函数
def verify_message(public_key,signature,message):
    (x,y),s=signature
     # 将消息哈希为一个大整数
    e = int.from_bytes(sm3((hex(x)[2:]+hex(y)[2:]+message).encode('utf-8')), byteorder='big')
    if point_multiplication(s, (Gx, Gy), p, A)==point_addition((x,y),point_multiplication(e, public_key, p, A),p,A):
        return True
    else:
        return False

def batch_verify(public_key,signature,message):
    number=len(message)
    left = None
    right = None
    R = None
    ep = None
    e = 0
    s = 0
    for i in range(number):
        e = int.from_bytes(sm3((hex(signature[i][0][0])[2:]+hex(signature[i][0][1])[2:]+message[i]).encode('utf-8')), byteorder='big')
        s = s + signature[i][1]
        R = point_addition(R, signature[i][0], p, A)
        ep = point_addition(ep ,point_multiplication(e, public_key[i], p, A),p,A)
    left = point_addition(left, point_multiplication(s, (Gx, Gy), p, A), p, A)
    right = point_addition(R ,ep,p,A)
    if left==right :
        return True
    else:
        return False

a=400
private_key=[]
public_key=[]
for i in range (a) :       
    x,y = generate_key_pair()
    private_key.append(x)
    public_key.append(y)

# 要签名的消息
message = ["Hello, ECDSA!","sadgadhfdgdfs","dsgagfafsd","asgasshgaggfd"]
message=message*int(a/4)
signature=[]
start_time = time.time()  # 记录开始时间    
# 使用私钥对消息进行签名
for i in range(a):
    signature.append (sign_message( message[i],private_key[i]))
end_time = time.time()    # 记录结束时间
elapsed_time = end_time - start_time
print("执行时间：", elapsed_time, "秒")

start_time = time.time()  # 记录开始时间    
# 使用私钥对消息进行签名
hello=[]
for i in range(a):
    hello.append (verify_message(public_key[i],signature[i],message[i]))
end_time = time.time()    # 记录结束时间
elapsed_time = end_time - start_time
print("执行时间：", elapsed_time, "秒")

start_time = time.time()  # 记录开始时间    
# 使用私钥对消息进行签名

hello1= batch_verify(public_key,signature,message)
end_time = time.time()    # 记录结束时间
print(hello1)
elapsed_time = end_time - start_time
print("执行时间：", elapsed_time, "秒")


