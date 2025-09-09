def encrypt(txt, key):
    lst = []
    for i in txt:
        # XOR the character with the key and convert to binary
        v = bin(ord(i) ^ key)[2:] + '1'
        nz = 8 - len(v)
        v = "0" * nz + v
        lst.append(v)
    a = "".join(lst)
    # Perform circular shift by 13
    a = a[13:] + a[:13]
    return a

def decrypt(txt, key):
    # Reverse the circular shift by 13
    txt = txt[-13:] + txt[:-13]
    lst = [txt[i:i+8] for i in range(0, len(txt), 8)]
    decrypted = ""
    for i in lst:
        # XOR the decoded binary character with the key
        decrypted += chr(int(i[:-1], 2) ^ key)
    return decrypted

# Define a key for XOR operation
key = 42

data = "S@rv3sh_is_0n_4_th3_w0r1d!"
print("Original Data:", data)

# Encrypt with the given key
Encrypted_data = encrypt(data, key)
print(f"Encrypted_data = {Encrypted_data}")

# Decrypt with the same key
Decrypted_data = decrypt(Encrypted_data, key)
print(f"Decrypted_data = {Decrypted_data}")
