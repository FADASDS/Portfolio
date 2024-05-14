class Polibius:
    def __init__(self):
        self.__n = 8
        self.__m = 9
        self.__table = []
        self.source_message = ""
        self.enc = []
        self.decoded_message = ""
        self.__create_table()

    def __create_table(self):

        s = 'А'

        for i in range(self.__n):
            row = []
            for j in range(self.__m):
                if i == 0 and j == 6:
                    row.append('Ё')
                elif i == 4 and j == 3:
                    row.append('ё')
                else:
                    row.append(s)
                    s = chr(ord(s) + 1)
            self.__table.append(row)

        self.__table[7][3] = ' '
        self.__table[7][4] = '.'
        self.__table[7][5] = ':'
        self.__table[7][6] = '!'
        self.__table[7][7] = '?'
        self.__table[7][8] = ','

    def code_message(self):
        self.enc = []
        length = len(self.source_message)

        for char in self.source_message:
            for p in range(self.__n):
                for j in range(self.__m):
                    if char == self.__table[p][j]:
                        result = str(p + 1) + str(j + 1)
                        self.enc.append(int(result))

    def decode_message(self):

        for code in self.enc:
            s = str(code)

            for p in range(self.__n):
                if int(s[0]) - 1 == p:
                    for j in range(self.__m):
                        if int(s[1]) - 1 == j:
                            self.decoded_message += self.__table[p][j]

