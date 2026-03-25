from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad

data = bytearray(get_random_bytes(1000))
key = get_random_bytes(16)
iv = get_random_bytes(16)

def flip_bit(data, byte_index, bit_index):
    data[byte_index] ^= (1 << bit_index)

def count_corrupted_blocks(original, decrypted):
    block_size = 16
    corrupted_blocks = 0

    for i in range(0, len(original), block_size):
        if original[i:i+block_size] != decrypted[i:i+block_size]:
            corrupted_blocks += 1

    return corrupted_blocks

modes = {
    "ECB": AES.MODE_ECB,
    "CBC": AES.MODE_CBC,
    "CFB": AES.MODE_CFB,
    "OFB": AES.MODE_OFB
}

for name, mode in modes.items():
    print(f"\n=== MODE: {name} ===")

    if mode == AES.MODE_ECB:
        cipher = AES.new(key, mode)
        ciphertext = cipher.encrypt(pad(bytes(data), 16))
    elif mode == AES.MODE_CBC:
        cipher = AES.new(key, mode, iv=iv)
        ciphertext = cipher.encrypt(pad(bytes(data), 16))
    else:
        cipher = AES.new(key, mode, iv=iv)
        ciphertext = cipher.encrypt(bytes(data))

    corrupted = bytearray(ciphertext)
    flip_bit(corrupted, 25, 0)

    if mode == AES.MODE_ECB:
        decipher = AES.new(key, mode)
        decrypted = unpad(decipher.decrypt(bytes(corrupted)), 16)
    elif mode == AES.MODE_CBC:
        decipher = AES.new(key, mode, iv=iv)
        decrypted = unpad(decipher.decrypt(bytes(corrupted)), 16)
    else:
        decipher = AES.new(key, mode, iv=iv)
        decrypted = decipher.decrypt(bytes(corrupted))

    corrupted_blocks = count_corrupted_blocks(data, decrypted)

    print("Số block bị lỗi:", corrupted_blocks)