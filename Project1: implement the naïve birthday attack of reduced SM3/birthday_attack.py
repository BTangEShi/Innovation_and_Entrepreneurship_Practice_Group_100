import hashlib
from gmssl import sm3
from string import ascii_letters, digits
from itertools import permutations
from time import time
ts='zxcvbnmasdfghjklpoiuytrewq0987654321'
st={}
def collision_SHA256(num):
    for item in permutations(ts,5):
        item=''.join(item)
        item=item.encode()
        hash_object = hashlib.sha256(item)
        hex_digest = hash_object.hexdigest()
        value=hex_digest[0:num]
        if(value not in st):
            st[value]=(item,1)
        else:
            print(st[value][0])
            print(item)
            print(value)
            break
def collision_SM3(num):
    for item in permutations(ts,5):
        item=''.join(item)
        item=item.encode()
        item_list=[i for i in item]
        hex_digest = sm3.sm3_hash(item_list)
        value=hex_digest[0:num]
        if(value not in st):
            st[value]=(item,1)
        else:
            print(st[value][0])
            print(item)
            print(value)
            break
def SM3(item):
    item=item.encode()
    item_list=[i for i in item]
    hex_digest = sm3.sm3_hash(item_list)
    Hash=hex_digest.encode()
    return Hash

def SHA256(item):
    item=item.encode()
    hash_object = hashlib.sha256(item)
    hex_digest = hash_object.hexdigest()
    return hex_digest.encode()

def Rho_SM3(num):
    item=b"202100460120"
    Hash1=SM3(item)
    Hash2=SM3(Hash1)
    while(True):
        if(Hash1[0:num]!=Hash2[0:num]):
            Hash1=SM3(Hash1)
            Hash2=SM3(SM3(Hash2))
        else:
            print(Hash1)
            print(Hash2)
            break

def Rho_SHA256(num):
    item=b"202100460120"
    Hash1=SHA256(item)
    Hash2=SHA256(Hash1)
    while(True):
        if(Hash1[0:num]!=Hash2[0:num]):
            Hash1=SHA256(Hash1)
            Hash2=SHA256(SHA256(Hash2))
        else:
            print(Hash1)
            print(Hash2)
            break
        
def Random_SHA256(num):
    item=b"202100460120"
    jk=False
    Hash_value=SHA256(item)
    for item in permutations(ts,5):
        item=''.join(item)
        item=item.encode()
        hash_object = hashlib.sha256(item)
        hex_digest = hash_object.hexdigest().encode()
        if(hex_digest[0:num]==Hash_value[0:num]):
            jk=True
            print(item)
            print(hex_digest)
        if(jk==True):
            break


start = time()
collision_SM3()
print('Time used:', time()-start)
start = time()
collision_SHA256()
print('Time used:', time()-start)


'''
'''
#input_s=input("请输入字符串：")
start=time()
for i in range(1000):
    SM3("ssss")
print('Time used:', time()-start)

start=time()
for i in range(1000):
    SHA256("ssss")
print('Time used:', time()-start)



'''
start = time()
Random_SHA256(2)
print('Time used:', time()-start)
start = time()
Random_SHA256(4)
print('Time used:', time()-start)
start = time()
Random_SHA256(6)
print('Time used:', time()-start)
start = time()
Random_SHA256(8)
print('Time used:', time()-start)



start = time()
Rho_SHA256(2)
print('Time used:', time()-start)

start = time()
Rho_SHA256(4)
print('Time used:', time()-start)

start = time()
Rho_SHA256(6)
print('Time used:', time()-start)

start = time()
Rho_SHA256(8)
print('Time used:', time()-start)
'''
