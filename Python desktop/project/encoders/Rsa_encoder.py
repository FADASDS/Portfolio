import random
import math

class RSA:
    def __init__(self):
        self.__size = 250
        self.__n = None
        self.__prime = set()
        self.source_msg = ""
        self.public_key = None
        self.private_key = None
        self.__primefiller()
        self.__setkeys()
        self.encrypted_msg = []
        self.decrypted_msg = ""

    def __primefiller(self):
        seive = [True] * self.__size
        seive[0] = False
        seive[1] = False
        for i in range(2, self.__size):
            for j in range(i * 2, self.__size, i):
                seive[j] = False

        for i in range(len(seive)):
            if seive[i]:
                self.__prime.add(i)

    def __pickrandomprime(self):
        k = random.randint(0, len(self.__prime) - 1)
        it = iter(self.__prime)
        for _ in range(k):
            next(it)

        ret = next(it)
        self.__prime.remove(ret)
        return ret

    def __setkeys(self):
        prime1 = self.__pickrandomprime()
        prime2 = self.__pickrandomprime()
        
        self.__n = prime1 * prime2
        fi = (prime1 - 1) * (prime2 - 1)

        e = 2
        while True:
            if math.gcd(e, fi) == 1:
                break
            e += 1

        self.public_key = e
        d = 2
        while True:
            if (d * e) % fi == 1:
                break
            d += 1
        self.private_key = d


    def __encrypt(self, number):
        e = self.public_key
        encrypted_text = pow(number, e, self.__n)
        return encrypted_text

    def __decrypt(self, number):
        d = self.private_key
        decrypted = pow(number, d, self.__n)
        return decrypted

    def encoder(self):
        self.encrypted_msg = [self.__encrypt(char) for char in self.source_msg.encode('cp1251')]

    def decoder(self):
        decrypted_bytes = [self.__decrypt(char) for char in self.encrypted_msg]
        self.decrypted_msg = bytes(decrypted_bytes).decode('cp1251')
