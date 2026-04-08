import random
from Crypto.Util.number import getPrime, inverse
import base64

def generate_keys(bits=512):
    p = getPrime(bits)
    q = getPrime(bits)
    n = p * q
    f = (p-1)*(q-1)
    
    e = 65537
    d = inverse(e, f)
    
    return (e, n), (d, n)

def encrypt_number(m, key):
    e, n = key
    return pow(m, e, n)

def decrypt_number(c, key):
    d, n = key
    return pow(c, d, n)

def string_to_int(msg):
    return int.from_bytes(msg.encode(), 'big')

def int_to_string(num):
    return num.to_bytes((num.bit_length()+7)//8, 'big').decode()


def encrypt_string(msg, pubkey):
    m = string_to_int(msg)
    c = encrypt_number(m, pubkey)
    
    c_bytes = c.to_bytes((c.bit_length()+7)//8, 'big')
    return base64.b64encode(c_bytes).decode()

def decrypt_string(cipher_b64, privkey):
    c_bytes = base64.b64decode(cipher_b64)
    c = int.from_bytes(c_bytes, 'big')
    
    m = decrypt_number(c, privkey)
    return int_to_string(m)


if __name__ == "__main__":
    pub, priv = generate_keys(512)
    
    print("Public Key:", pub)
    print("Private Key:", priv)

    msg = "The University of Information Technology"
    
    cipher = encrypt_string(msg, pub)
    print("Cipher (Base64):", cipher)

    plain = decrypt_string(cipher, priv)
    print("Decrypted:", plain)