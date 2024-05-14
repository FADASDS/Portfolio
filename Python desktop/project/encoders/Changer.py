class Changer:
    def __init__(self):
        self.__n = 72
        self.__alphabet = ""
        self.key = ""
        self.source_msg = ""
        self.enc = []
        self.encrypted_msg = ""
        self.decrypted_msg = ""
        self.__create_alphabet()
        

    def get_key_nums(self):

        self.__key_nums = [self.__alphabet.find(char) for char in self.key]

    def __create_alphabet(self):
        self.__n = 72
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
        length = len(self.source_msg)
        self.encrypted_msg = ""
        j = 0

        for i in range(length):
            poz = (self.__alphabet.find(self.source_msg[i]) + self.__key_nums[j]+1)% len(self.__alphabet)
            self.encrypted_msg += self.__alphabet[poz-1]

            print(poz)
            j += 1
            if j == len(self.__key_nums):
                j = 0

    def decode_message(self):
        self.decrypted_msg = ""
        length = len(self.encrypted_msg)
        j = 0

        for i in range(length):
            poz = (self.__alphabet.find(self.encrypted_msg[i]) - self.__key_nums[j]+ len(self.__alphabet)) % len(self.__alphabet)
            self.decrypted_msg += self.__alphabet[poz]
            j += 1
            if j == len(self.__key_nums):
                j = 0
