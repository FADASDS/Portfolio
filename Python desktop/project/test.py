import struct
import numpy as np
import random
import os

def generate_key_table():
    bytes_str = np.random.bytes(2560)
    key_table = [bytes_str[i:i+10] for i in range(0, len(bytes_str), 10)]
    return key_table

def generate_masks(key_table):

    mask1 = key_table[0]
    mask2 = key_table[128]
    for key in key_table[1:128]:
        mask1 = bytes([x ^ y for x, y in zip(mask1, key)])
    for key in key_table[129:]:
        mask2 = bytes([x ^ y for x, y in zip(mask2, key)])
    return mask1, mask2

def process_block(block, key_table, mask):
    result = bytearray()
    for i in range(10):
        block_byte = block[i] ^ mask[i]
        key_index = block_byte % 256
        selected_key = key_table[key_index]
        processed_byte = block_byte ^ selected_key[i]
        result.append(processed_byte)
    return bytes(result)

def encrypt_data(data, key_table, mask1, mask2):
    encrypted_data = bytearray()
    data_block = bytearray()
    for block in [data[i:i+10] for i in range(0, len(data), 10)]:
        data_block = process_block(block, key_table, mask1)
        data_block = process_block(data_block, key_table, mask2)
        encrypted_data.extend(data_block)
    [print(byte) for byte in data_block]
    #print(encrypted_data)
    return bytes(encrypted_data)

def decrypt_data(data, key_table, mask1, mask2):
    decrypted_data = bytearray()
    data_block = bytearray()
    for block in [bytes(reversed(data))[i:i+10] for i in range(0, len(data), 10)]:
        data_block = process_block(block, key_table, bytes(reversed(mask2)))
        data_block = process_block(data_block, key_table,  bytes(reversed(mask1)))
        decrypted_data.extend(reversed(data_block))
    return bytes(decrypted_data)

# Пример использования
key_table = generate_key_table()
mask1, mask2 = generate_masks(key_table)
msg = "Привет,как"
dat = msg.encode('cp1251')
enc = encrypt_data(dat, key_table, mask1, mask2)
dec = decrypt_data(enc, key_table, mask1, mask2)
print(dec.decode('cp1251'))
#[print(byte) for byte in enc]

#[print(int.from_bytes(byte)) for byte in bytes_str[:10]]
#print(int.from_bytes(bytes_str[:1]))