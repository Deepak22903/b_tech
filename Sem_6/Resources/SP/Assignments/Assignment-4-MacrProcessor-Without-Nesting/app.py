code = open("input.txt", 'r')
out = open("output.txt", 'w')
mnt = []
mbt = []
key_words = {'load', 'store', 'add', 'sub', 'mult', 'div', 'END'}

def remove_char(s, l):
    return [c for c in l if c != s]

def remove_newline(l):
    return [s[:-1] if s.endswith('\n') else s for s in l]

def add_newline(l):
    l[-1] += '\n'
    return l

def replace_char(param, l):
    return [param.get(s, s) for s in l]

def replace_char_2(l1, l2):
    return [l1[int(s[1:])] if s.startswith('#') else s for s in l2]

def add_output(l, outpt):
    outpt.write(' '.join(add_newline(l)))

def get_mbt_index(l):
    for i, (name, args, index) in enumerate(mnt):
        if name == l[0] and args == len(l) - 1:
            return index
    return -1

def nested_expand(l, ef, df):
    l = remove_char(',', l)
    ind = get_mbt_index(l)
    while ef and not df:
        l1 = mbt[ind].copy()
        ind += 1
        if l1[0] == 'MEND':
            ef = False
        elif l1[0] not in key_words:
            l1 = replace_char_2(l, l1)
            nested_expand(l1, ef, df)
        else:
            l1 = replace_char_2(l, l1)
            add_output(l1, out)

while True:
    line = code.readline()
    if not line:
        break
    line = remove_newline(line.split())
    line = remove_char('', line)
    if line[0] == 'MACRO':
        paramenter = {}
        mnt_entry = [line[1], len(line) - 2, len(mbt)]
        mnt.append(mnt_entry)
        count = 1
        for i in range(2, len(line)):
            paramenter[line[i]] = '#' + str(count)
            count += 1
    elif line[0] not in key_words:
        mbt.append(replace_char(paramenter, line))
    elif line[0] == 'MEND':
        del paramenter
    else:
        e_flag, d_flag = True, False
        while e_flag and not d_flag:
            index = get_mbt_index(line)
            if index == -1:
                add_output(line, out)
                break
            line1 = mbt[index].copy()
            add_output(replace_char_2(line, line1), out)
            if line1[0] == 'MEND':
                e_flag = False
            elif line1[0] not in key_words:
                nested_expand(replace_char_2(line, line1), e_flag, d_flag)
            else:
                add_output(replace_char_2(line, line1), out)