def vigenere_encrypt(plaintext, keyword):
    result = ""
    keyword_repeated = (keyword * (len(plaintext) // len(keyword) + 1))[:len(plaintext)]
    
    for p, k in zip(plaintext, keyword_repeated):
        if p.isalpha():
            shift = ord(k.upper()) - ord('A')
            base = ord('A') if p.isupper() else ord('a')
            result += chr((ord(p) - base + shift) % 26 + base)
        else:
            result += p
            
    return result

def vigenere_decrypt(ciphertext, keyword):
    result = ""
    keyword_repeated = (keyword * (len(ciphertext) // len(keyword) + 1))[:len(ciphertext)]
    
    for c, k in zip(ciphertext, keyword_repeated):
        if c.isalpha():
            shift = ord(k.upper()) - ord('A')
            base = ord('A') if c.isupper() else ord('a')
            result += chr((ord(c) - base - shift) % 26 + base)
        else:
            result += c
            
    return result

# Example usage:
plaintext = input("Please enter the plain text:")
keyword = "ah"
encrypted = vigenere_encrypt(plaintext, keyword)
decrypted = vigenere_decrypt(encrypted, keyword)

print(f"Original: {plaintext}")
print(f"Encrypted: {encrypted}")
print(f"Decrypted: {decrypted}")
