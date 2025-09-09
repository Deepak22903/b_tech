import re
from collections import defaultdict
from pprint import pprint

def read_productions(file_path):
    productions = []
    
    # Read the file line by line
    with open(file_path, 'r') as file:
        for line in file:
            line = line.strip()
            if line:
                productions.append(line)

    main=[]

    for i in productions:
        lst=[]
        i=i.split('->')
        lst.append(i[0])

        i=i[1].split('|')
        temp=[]
        for j in i:
            temp.append(j)
        lst.append(temp)

        main.append(lst)
    
    return main


def extract_non_terminals(productions):
    non_terminals = set()

    for production in productions:
        non_terminal = production[0]
        non_terminals.add(non_terminal)

    return non_terminals

# Function to extract terminals from the list of productions
def extract_terminals(productions, non_terminals):
    terminals = set()

    for production in productions:
        for symbols in production[1]:
            for symbol in symbols:
                if symbol not in non_terminals and symbol != 'e' and symbol not in terminals:
                    terminals.add(symbol)

    return terminals

file_path = 'grammar.txt'

productions = read_productions(file_path)
pprint(productions)

non_terminals = extract_non_terminals(productions)

terminals = extract_terminals(productions, non_terminals)

print("Non-terminals:")
for nt in non_terminals:
    print(nt)

print("\nTerminals:")
for t in terminals:
    print(t)

print("\n-------------------------------------------------------------------\n")

first_set = defaultdict(set)

def calculate_first_set(nt):
    for production in productions:
        lhs, rhs = production
        symbols = rhs
        if lhs == nt:
            for symbol in symbols:
                for c in symbol:
                    if c in non_terminals:
                        first_set[nt] |= calculate_first_set(c)
                        if 'e' not in first_set[c]:
                            break
                    else:
                        first_set[nt].add(c)
                        break
    
    return first_set[nt]


for nt in non_terminals:
    calculate_first_set(nt)

for nt in non_terminals:
    print(f"FIRST({nt}) = {{ {', '.join(first_set[nt])} }}")


print("\n-------------------------------------------------------------------\n")

follow_set = defaultdict(set)

def calculate_follow_set(nt):
    if nt == 'E':
        follow_set[nt].add('$')
    
    for production in productions:
        lhs, rhs = production
        symbols = rhs
        for symbol in symbols:
            for i, c in enumerate(symbol):
                if c == nt:
                    if i == len(symbol) - 1:
                        if lhs != nt:
                            follow_set[nt] |= calculate_follow_set(lhs)
                    else:
                        next_symbol = symbol[i + 1]
                        if next_symbol in non_terminals:
                            follow_set[nt] |= first_set[next_symbol]
                            if 'e' in first_set[next_symbol]:
                                follow_set[nt] |= calculate_follow_set(next_symbol)
                        else:
                            follow_set[nt].add(next_symbol)
    
    return follow_set[nt]


for nt in non_terminals:
    calculate_follow_set(nt)

for nt in non_terminals:
    if 'e' in follow_set[nt]:
        follow_set[nt].remove('e')

for nt in non_terminals:
    print(f"FOLLOW({nt}) = {{ {', '.join(follow_set[nt])} }}")

