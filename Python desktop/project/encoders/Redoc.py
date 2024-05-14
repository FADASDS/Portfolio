import numpy as np

class Redoc:

    def __init__(self):
        self.source_msg = ""
        self.bytes_str = ""
        self.__mask1 = None
        self.__mask2 = None
        self.__key_table = self.__generate_key_table()
        self.__generate_masks()
        self.encrypted_msg = None
        self.decrypted_msg = ""

    def __generate_key_table(self):
        bytes_str = np.random.bytes(2560)
        self.bytes_str = bytes_str
        key_table = [bytes_str[i:i+10] for i in range(0, len(bytes_str), 10)]
        return key_table

    def __generate_masks(self):

        mask1 = self.__key_table[0]
        mask2 = self.__key_table[128]
        for key in self.__key_table[1:128]:
            mask1 = bytes([x ^ y for x, y in zip(mask1, key)])
        for key in self.__key_table[129:]:
            mask2 = bytes([x ^ y for x, y in zip(mask2, key)])
        self.__mask1 = mask1
        self.__mask2 = mask2

    def __process_block(self, block, mask, par = 0):
        block = bytearray(block)
        for i in range(len(block)):
            block_byte = block[i] ^ mask[i]
            key_index = block_byte % 256
            selected_key = bytes(reversed(self.__key_table[key_index])) if par == 1 else self.__key_table[key_index]
            for j in range(len(block)):
                if(j!=i):
                    block[j] = block[j]^selected_key[j]

        return bytes(block)

    def encrypt_data(self):
        data = self.source_msg.encode('cp1251')
        data = self.__pad_bytes_to_length(data, 10)
        encrypted_data = bytearray()
        data_block = bytearray()
        for block in [data[i:i+10] for i in range(0, len(data), 10)]:
            data_block = self.__process_block(block, self.__mask1)
            data_block = self.__process_block(data_block, self.__mask2)
            encrypted_data.extend(data_block)

        self.encrypted_msg = bytes(encrypted_data)

    def decrypt_data(self):
        data = self.encrypted_msg
        decrypted_data = bytearray()
        data_block = bytearray()
        for block in [bytes(reversed(data))[i:i+10] for i in range(0, len(data), 10)]:
            data_block = self.__process_block(block, bytes(reversed(self.__mask2)), 1)
            data_block = self.__process_block(data_block,  bytes(reversed(self.__mask1)), 1)
            decrypted_data[:0] = reversed(data_block)
        self.decrypted_msg = bytes(decrypted_data).decode('cp1251')

    def __pad_bytes_to_length(self, data, target_length):
        current_length = len(data)
        while(current_length % target_length !=0):
            padding_bytes = b'\x00'  
            data += padding_bytes
            current_length = len(data)
        return data