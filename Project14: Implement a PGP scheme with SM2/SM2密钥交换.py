import base64
import binascii
import secrets
from gmssl import sm2, func
from tinyec import registry
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad
###########################AES######################################
def aes_256_encrypt(key, plaintext):
    iv = get_random_bytes(AES.block_size)
    cipher = AES.new(key, AES.MODE_CBC, iv)
    ciphertext = cipher.encrypt(pad(plaintext.encode(), AES.block_size))
    return iv + ciphertext

def aes_256_decrypt(key, ciphertext):
    iv = ciphertext[:AES.block_size]
    ciphertext = ciphertext[AES.block_size:]
    cipher = AES.new(key, AES.MODE_CBC, iv)
    plaintext = unpad(cipher.decrypt(ciphertext), AES.block_size)
    return plaintext.decode()

##########################密钥交换协议#############################

def compress(pubKey):
    return hex(pubKey.x) + hex(pubKey.y % 2)[2:]
 
curve = registry.get_curve('brainpoolP256r1')
 
alicePrivKey = secrets.randbelow(curve.field.n)
alicePubKey = alicePrivKey * curve.g
print("Alice public key:", compress(alicePubKey))
 
bobPrivKey = secrets.randbelow(curve.field.n)
bobPubKey = bobPrivKey * curve.g
print("Bob public key:", compress(bobPubKey))
 
print("Now exchange the public keys (e.g. through Internet)")
 
aliceSharedKey = alicePrivKey * bobPubKey
print("Alice shared key:", compress(aliceSharedKey))
 
bobSharedKey = bobPrivKey * alicePubKey
print("Bob shared key:", compress(bobSharedKey))
 
print("Equal shared keys:", aliceSharedKey == bobSharedKey)


#############################加解密#################################
private_key = '00B9AB0B828FF68872F21A837FC303668428DEA11DCD1B24429D0C99E24EED83D5'
public_key = 'B9C9A6E04E9C91F7BA880429273747D7EF5DDEB0BB2FF6317EB00BEF331A83081A6994B8993F3F5D6EADDDB81872266C87C018FB4162F5AF347B483E24620207'
sm2_crypt = sm2.CryptSM2(public_key=public_key, private_key=private_key)

##加密和解密
#数据和加密后数据为bytes类型

session_key= compress(aliceSharedKey)[35:].encode()
print("session_key:",session_key)
enc_session_key = sm2_crypt.encrypt(session_key)
print("enc_session_key:",enc_session_key)
data="TangShi"
print("data:",data)
encrypted_data = aes_256_encrypt(session_key, data)
print("Encrypted:", encrypted_data.hex())


dec_session_key=sm2_crypt.decrypt(enc_session_key )
print("dec_session_key:",dec_session_key)
dec_data=aes_256_decrypt(dec_session_key, encrypted_data)
print("Decrypted:", dec_data)
##dec_data =sm2_crypt.decrypt(enc_data)
##assert dec_data == data



