from gmssl import sm3
from time import time
from itertools import permutations
import random
helloworld='abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789'


def SM3(message):
    message=message.encode()
    message_list=[i for i in message]
    hex_digest = sm3.sm3_hash(message_list)
    Hash=hex_digest.encode()
    return Hash

def birthday_attack(hash_length=10):
    hash_dict = {}
    collision_found = False
    for _ in  range(100000000):
        message = ''.join(random.choice(helloworld) for i in range(hash_length))
        hash_value = SM3(message)

        if hash_value[0:hash_length] in hash_dict:
            a=hash_dict[hash_value[0:hash_length]]
            print("Collision Found!")
            print("Original Message 1:", message)
            print("Original Message 2:",a)
            print("Hash Value1:", hash_value)
            print("Hash Value2:", SM3( a))
            collision_found = True
            break
        else:
            hash_dict[hash_value[0:hash_length]] = message

    if not collision_found:
        print("No collision found after", num_trials, "trials.")




birthday_attack(5)


