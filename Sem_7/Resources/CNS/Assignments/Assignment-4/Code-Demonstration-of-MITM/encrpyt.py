def encrypt(txt):
    lst=[]
    for i in txt:
        v=(bin(ord(i))[2:])+'1'
        nz=8-len(v)
        v="0"*nz+v
        lst.append(v)
    a="".join(lst)
    a=a[13:]+a[:13]
    return a
    

def decrypt(txt):
    txt=txt[-13:]+txt[:-13]
    lst= [txt[i:i+8] for i in range(0, len(txt), 8)]
    decrypted=""
    for i in lst:
        decrypted+=chr(int(i[:-1],2))
    return decrypted

data="S@rv3sh_is_0n_4_th3_w0r1d!"
print("Original Data:-",data)
Encrypted_data=encrypt(data) 
print(f"{Encrypted_data = }")
Decrypted_data=decrypt(Encrypted_data)
print(f"{Decrypted_data = }")
#S@rv3sh_is_0n_4_th3_w0r1d!