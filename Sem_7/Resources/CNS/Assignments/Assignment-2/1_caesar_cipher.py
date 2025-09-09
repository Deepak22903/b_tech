import string
from random import randint

def caeser_encrypt(word,key):
    letters=string.ascii_lowercase+string.ascii_lowercase+string.ascii_uppercase+string.ascii_uppercase
    enc=""
    for i in word:
        if i in letters:
            enc+=letters[(letters.index(i)+key)]
        else:
            enc+=i
    
    return enc

def caeser_decrypt(word,key):
    letters=string.ascii_lowercase+string.ascii_lowercase+string.ascii_uppercase+string.ascii_uppercase
    dec=""
    for i in word:
        if i in letters:
            dec+=letters[(letters.index(i)-key)]
        else:
            dec+=i
    
    return dec

testCase1="Hello World"
key=randint(1,25)
print("Original Text:",testCase1)
print("Key:",key)

encrypted=caeser_encrypt(testCase1,key)
print("Encrypted Text:",encrypted)

decrypted=caeser_decrypt(encrypted,key)
print("Decrypted Text:",decrypted)


