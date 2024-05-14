import numpy as np
class Matrix:
    def __init__(self):
        self.__n = 72
        self.__size = 3
        self.__alphabet = ""
        self.source_msg = ""
        self.enc = []
        self.encrypted_msg = []
        self.decrypted_msg = ""
        self.__create_alphabet()
        self.key_matrix = self.__init_key_matrix()
        self.__list_for_decoding = []

    def __init_key_matrix(self):

        key_matrix = np.random.randint(low=1, high=10, size=(self.__size, self.__size))
        while np.linalg.det(key_matrix) <= 0:
            key_matrix = np.random.randint(low=1, high=10, size=(self.__size, self.__size))

        return key_matrix
    

    def __create_alphabet(self):
        s = 'А'
        self.__alphabet = ""
        for i in range(self.__n - 6):
            if i == 6:
                self.__alphabet += 'Ё'
            elif i == 40:
                self.__alphabet += 'ё'
            else:
                self.__alphabet += s
                s = chr(ord(s) + 1)

        self.__alphabet += ' '
        self.__alphabet += '.'
        self.__alphabet += ':'
        self.__alphabet += '!'
        self.__alphabet += '?'
        self.__alphabet += ','

    def code_message(self):
        
        self.__list_for_decoding = []
        self.encrypted_msg = []
        encode_array = self.__form_encode_array()
        for group in encode_array:
            array = np.matmul(self.key_matrix, group)

            self.__list_for_decoding.append(list(array))
            for element in array:
                self.encrypted_msg.append(element)
        if len(self.encrypted_msg)>len(self.source_msg):
            self.encrypted_msg = self.encrypted_msg[0:len(self.source_msg)]

    def __form_encode_array(self):
        
        length = len(self.source_msg)
        k=0
        group_array = []
        msg_array = []

        while k < length:
            for i in range(self.__size):
                group_array.append(self.__alphabet.find(self.source_msg[k]))
                k+=1
                if k==length:
                    break
            while(len(group_array)<self.__size):
                group_array.append(0)
            msg_array.append(group_array.copy())
            group_array.clear()

        return msg_array

    def decode_message(self):
        self.decrypted_msg = ""
        decode_array = []
        for group in self.__list_for_decoding:
            array = np.matmul(np.linalg.inv(self.key_matrix), group)
            for el in array:
                decode_array.append(round(el))
        for i in range(len(self.source_msg)):
            self.decrypted_msg += self.__alphabet[decode_array[i]]