PTA = ' abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789'
CTA = ' qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM0123456789'

def mono_alpabetic_cipher(pt):
    ans = ''
    for i in pt:
        try:
            ans += CTA[PTA.index(i)]
        except:
            ans += i
    return ans

def mono_alpabetic_decipher(ct):
    ans = ''
    for i in ct:
        try:
            ans += PTA[CTA.index(i)]
        except:
            ans += i
    return ans

testCase1="Hello World"
print("Original Text:",testCase1)

encrypted=mono_alpabetic_cipher(testCase1)
print("Encrypted Text:",encrypted)

decrypted=mono_alpabetic_decipher(encrypted)
print("Decrypted Text:",decrypted)
