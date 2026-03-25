from Crypto.Cipher import AES
key = b'1234567890123456'

iv = b'abcdefghijklmnop'

plaintext = b"UIT_LAB_UIT_LAB_UIT_LAB_UIT_LAB_"

print("Plaintext:", plaintext)
print("Length:", len(plaintext), "bytes")

# 1. AES ECB MODE
cipher_ecb = AES.new(key, AES.MODE_ECB)
ct_ecb = cipher_ecb.encrypt(plaintext)

# 2. AES CBC MODE
cipher_cbc = AES.new(key, AES.MODE_CBC, iv)
ct_cbc = cipher_cbc.encrypt(plaintext)

print("\nAES ECB Ciphertext (HEX):")
print(ct_ecb.hex())

print("\nAES CBC Ciphertext (HEX):")
print(ct_cbc.hex())

print("\nECB Blocks:")
for i in range(0, len(ct_ecb), 16):
    print(f"Block {i//16 + 1}: {ct_ecb[i:i+16].hex()}")

print("\nCBC Blocks:")
for i in range(0, len(ct_cbc), 16):
    print(f"Block {i//16 + 1}: {ct_cbc[i:i+16].hex()}")