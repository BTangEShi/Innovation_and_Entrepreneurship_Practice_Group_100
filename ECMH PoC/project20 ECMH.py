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

#将一个字符串转化成椭圆曲线上的点
def hash_to_point(message):
    hashed_message=message
    # 计算消息的哈希值
    i=0
    while(True):
        i=i+1
        if(i%100000==0):
            print(i)
        hashed_message = sm3(hashed_message)
         
        # 将哈希值的前半部分和后半部分分别作为 x 和 y 坐标
        x = int.from_bytes(hashed_message, byteorder='big')
        y = calculate_y_coordinate(x)


        if is_point_on_elliptic_curve(x,y):
            print(is_point_on_elliptic_curve(x,y))
            return (x,y)

#将UTXO列表转化成椭圆曲线上的点
def UTXOinit(UTXOlist):
    middle=hash_to_point(UTXOlist[0])
    for i in UTXOlist[1:]:
        middle=point_addition(middle,hash_to_point(i),p,A)
    return middle

def UTXOadd(hello,UTXO):
    return point_addition(UTXO,hash_to_point(hello),p,A)

def UTXOsub(hello,UTXO):
    return point_subtraction(UTXO,hash_to_point(hello),p,A)
a= [b'76a9140123456789abcdefabcdefabcdefabcdef0123456789a88ac', b'76a914fedcba9876543210fedcba9876543210fedcba9876a88ac', b'76a914abcdefabcdef0123456789abcdefabcdefabcdef012345a88ac']
hello=b'846547864568656dfdfa48658548651'
# 示例
message = b'asgags'
point = UTXOinit(a)
print("椭圆曲线上的点：",point)
point1=UTXOadd(hello,point)
print("新加入元素后的点： ",point1)
point1=UTXOsub(hello,point1)
print("新加入元素后的点： ",point1)






