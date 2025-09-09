import copy


def key_fun():
    var = input("\nEnter your key: ")
    var2 = []
    for i in var:
        if i in var2:
            pass
        else:
            var2.append(i)
    # i is always replaced by j
    for n, i in enumerate(var2):
        if i == 'i':
            var2[n] = 'j'
    return var2


def data_fun(var):
    alpha = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'j', 'k', 'l',
             'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
    for i in var:
        if i in alpha:
            alpha.remove(i)
    var2 = copy.copy(var)
    var2.reverse()
    for i in var2:
        alpha.insert(0, i)
    return alpha


def createMatrix(dataList):
    mat = []
    for i in range(5):
        rowList = []
        for j in range(5):
            rowList.append(dataList[5 * i + j])
        mat.append(rowList)
    return mat


def pt_fun(pt):
    ans = list(pt)
    var = len(ans)
    while var > 0:
        for i in range(len(ans)-1):
            if ans[i] == ans[i + 1]:
                ans.insert(i + 1, 'x')
                break
        var -= 1
    if len(ans) % 2 != 0:
        ans += 'x'
    return ans


def encrypt():
    plaintext = input("\nEnter your plaintext: ")
    key = key_fun()
    data = data_fun(key)
    mat = createMatrix(data)
    pt = pt_fun(plaintext)
    ans = []
    ct = ""
    for i in range(0, len(pt), 2):
        text1 = pt[i]
        text2 = pt[i + 1]
        for j in range(5):
            for k in range(5):
                if mat[j][k] == text1:
                    row1 = j
                    col1 = k
                if mat[j][k] == text2:
                    row2 = j
                    col2 = k
        if row1 == row2:
            ans.append(mat[(row1+1) % 5][col1])
            ans.append(mat[(row2+1) % 5][col2])
        elif col1 == col2:
            ans.append(mat[row1][(col1+1) % 5])
            ans.append(mat[row2][(col2+1) % 5])
        else:
            ans.append(mat[row1][col2])
            ans.append(mat[row2][col1])
    for i in ans:
        ct += i
    return ct


def decrypt():
    ciphertext = input("\nEnter your ciphertext: ")
    key = key_fun()
    data = data_fun(key)
    mat = createMatrix(data)
    ans = []
    pt = ""
    for i in range(0, len(ciphertext), 2):
        text1 = ciphertext[i]
        text2 = ciphertext[i + 1]
        for j in range(5):
            for k in range(5):
                if mat[j][k] == text1:
                    row1 = j
                    col1 = k
                if mat[j][k] == text2:
                    row2 = j
                    col2 = k
        if row1 == row2:
            ans.append(mat[(row1-1) % 5][col1])
            ans.append(mat[(row2-1) % 5][col2])
        elif col1 == col2:
            ans.append(mat[row1][(col1-1) % 5])
            ans.append(mat[row2][(col2-1) % 5])
        else:
            ans.append(mat[row1][col2])
            ans.append(mat[row2][col1])
    for i in ans:
        pt += i
    return pt


ct = encrypt()
print("\nYour ciphertext is: ", ct)
pt = decrypt()
print("\nYour plaintext is: ", pt)
