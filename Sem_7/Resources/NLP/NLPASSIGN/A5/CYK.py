from collections import defaultdict

def read_grammar(filename):
    unary_rules = defaultdict(set)  # A -> a
    binary_rules = defaultdict(set)  # A -> B C
    
    with open(filename, 'r') as file:
        for line in file:
            line = line.strip()
            if not line or '->' not in line:
                continue
            
            left, right = line.split('->')
            left = left.strip()
            right_symbols = right.strip().split()
            
            if len(right_symbols) == 1:
                unary_rules[right_symbols[0]].add(left)
            elif len(right_symbols) == 2:
                binary_rules[(right_symbols[0], right_symbols[1])].add(left)
    
    return unary_rules, binary_rules

def cky_parse(sentence, unary_rules, binary_rules, start='S'):
    words = sentence.split()
    n = len(words)
    
    table = []
    for i in range(n):
        row = []
        for j in range(n):
            row.append(set())
        table.append(row)
    
    for i, word in enumerate(words):
        if word in unary_rules:
            table[i][i].update(unary_rules[word])
    
    for length in range(2, n + 1):
        for i in range(n - length + 1):
            j = i + length - 1
            for k in range(i, j):
                for B in table[i][k]:
                    for C in table[k + 1][j]:
                        # add binary rules to table[i][j]
                        if (B, C) in binary_rules:
                            table[i][j].update(binary_rules[(B, C)])
    
    is_parsed = start in table[0][n - 1]

    return table, is_parsed

def display_table(table, file):
    file.write("CKY Table:\n")
    for row in table:
        file.write("[" + ", ".join("{" + ", ".join(cell) + "}" for cell in row) + "]\n")


if __name__ == "__main__":
    unary_rules, binary_rules = read_grammar('gramar.txt')

    sentence1 = "for the love of innovation"
    
    sentence2 = "she eats the fish"

    table1, is_parsed1 = cky_parse(sentence1, unary_rules, binary_rules)
    table2, is_parsed2 = cky_parse(sentence2, unary_rules, binary_rules)

    with open('output1.txt', 'w') as file:
        display_table(table1, file)

        if is_parsed1:
            file.write(f"\nThe sentence '{sentence1}' is successfully parsed!\n")
        else:
            file.write(f"\nThe sentence '{sentence1}' cannot be parsed by the grammar.\n")
    
    with open('output2.txt', 'w') as file:
        display_table(table2, file)

        if is_parsed2:
            file.write(f"\nThe sentence '{sentence2}' is successfully parsed!\n")
        else:
            file.write(f"\nThe sentence '{sentence2}' cannot be parsed by the grammar.\n")
