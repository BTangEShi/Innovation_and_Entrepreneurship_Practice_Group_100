import hashlib
import socket
import json
import secrets
import random
def serialize_dict(data):
    return json.dumps(data).encode('utf-8')

def deserialize_dict(data):
    return json.loads(data.decode('utf-8'))
ascii_letter="qwerytuioplkjmnhbgvfcdsxza1234567890"
S=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
HOST=socket.gethostname()
PORT=8080
S.bind((HOST,PORT))
print ('Server start at: %s:%s' %(HOST, PORT))
print ('wait for connection...')
S.listen(1)
born_year=1978
now_year=2021
prove_age=21
useable_year=2100
while True:
    conn,addr=S.accept()
    print("Connected by",addr)
    while True:
        seed=""
        for i in  range(16):
            seed+=ascii_letter[random.randint(0,len(ascii_letter)-1)]
        print("生成的种子：", seed)
        s=hashlib.sha256(seed.encode()).hexdigest()
        k=useable_year-born_year
        sig=s
        for i in range(k):
            sig=hashlib.sha256(sig.encode()).hexdigest()
        
        d0=now_year-prove_age-born_year
        p=s
        for i in range(d0):
            p= hashlib.sha256(p.encode()).hexdigest()
        conn.send(serialize_dict({"p":p,"sig":sig}))
        stop = input("Do you want to stop? (y/n): ").strip().lower()
        if stop == 'y':
            conn.send(serialize_dict({'num': -1}))
            break
    conn.close()
    break
S.close()
            
