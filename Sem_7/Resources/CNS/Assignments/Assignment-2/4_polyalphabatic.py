# Polyalphabatic cipher

def encrypt(text,key):
    ans = ''
    for i in range(len(text)):
        ans += chr((ord(text[i]) + ord(key[i % len(key)])) % 256)
    return ans

def decrypt(text,key):
    ans = ''
    for i in range(len(text)):
        ans += chr((ord(text[i]) - ord(key[i % len(key)])) % 256)
    return ans

print("Encrypted message",encrypt("hello","hi"))
print("Decrypted message",decrypt(encrypt("hello","hi"),"hi"))