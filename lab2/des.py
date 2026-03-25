from Crypto.Cipher import DES
from Crypto.Util.Padding import pad

def text_to_bits(data):
    return bin(int.from_bytes(data, 'big'))[2:].zfill(len(data) * 8)

def hamming_distance(b1, b2):
    return sum(x != y for x, y in zip(b1, b2))

def encrypt_des(text, key):
    key = key.ljust(8, '0')[:8].encode()
    cipher = DES.new(key, DES.MODE_ECB)
    return cipher.encrypt(pad(text.encode(), 8))

plaintext1 = "STAYHOME"
plaintext2 = "STAYHOMA"

key = "23520053"

c1 = encrypt_des(plaintext1, key)
c2 = encrypt_des(plaintext2, key)

b1 = text_to_bits(c1)
b2 = text_to_bits(c2)

dist = hamming_distance(b1, b2)
percent = (dist / len(b1)) * 100

print("Cipher 1:", b1)
print("Cipher 2:", b2)
print("Hamming Distance:", dist)
print("Tỷ lệ thay đổi (%):", percent)