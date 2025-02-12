key_words = ['load', 'store', 'add', 'sub', 'mul', 'div', 'END']

with open("input.txt", 'r') as code, open("output.txt", 'w') as out:
    mnt = []
    mbt = []
    params = {}
    for line in code:
        line = line.strip().split(" ")
        if line[0] == "MACRO":
            params = {}
            for i, param in enumerate(line[2:]):
                params[param] = f"#{i}"
            mnt.append([line[1], len(params), len(mbt)])
            mbt.append([])
        elif line[0] == "MEND":
            mbt.append([])
        elif line[0] in key_words:
            out.write(" ".join(line) + "\n")
        else:
            found_macro = False
            for i, macro in enumerate(mnt):
                if macro[0] == line[0] and macro[1] == len(line)-1:
                    found_macro = True
                    for mbt_line in mbt[macro[2]]:
                        replaced_line = [params.get(word, word) for word in mbt_line]
                        out.write(" ".join(replaced_line) + "\n")
            if not found_macro:
                out.write(" ".join(line) + "\n")
            else:
                mbt[-1].append(line)