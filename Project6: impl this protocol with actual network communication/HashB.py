import hashlib
import socket
import json
import time

def serialize_dict(data):
    return json.dumps(data).encode('utf-8')

def deserialize_dict(data):
    return json.loads(data.decode('utf-8'))

now_year=2021
prove_age=21
useable_year=2100

S=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
HOST=socket.gethostname()
PORT=8080
S.connect((HOST,PORT))
while True:
    data=S.recv(1024)
    message=deserialize_dict(data)
    p=message['p']
    sig=message['sig']
    print("sig:",sig)
    d1=useable_year-(now_year-prove_age)
    c_=p
    for i in range(d1):
        c_=hashlib.sha256(c_.encode()).hexdigest()
    print("c':",c_)
    if(c_==sig):
        print("Alice'age is older than ",prove_age)
    else:
        print("Alice wants to cheat me!")
    break
S.close()


    
