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

    main = []

    for i in productions:
        lst = []
        i = i.split('->')
        lst.append(i[0].strip())

        i = i[1].split('|')
        temp = []
        for j in i:
            temp.append(j.strip())
        lst.append(temp)

        main.append(lst)
    
    return main

def extract_non_terminals(productions):
    non_terminals = set()
    for production in productions:
        non_terminal = production[0]
        non_terminals.add(non_terminal)
    return non_terminals

def extract_terminals(productions, non_terminals):
    terminals = set()
    for production in productions:
        for symbols in production[1]:
            for symbol in symbols:
                if symbol not in non_terminals and symbol != 'e' and symbol not in terminals:
                    terminals.add(symbol)
    return terminals

def calculate_first_set(nt, productions, first_set, non_terminals):
    for production in productions:
        lhs, rhs = production
        symbols = rhs
        if lhs == nt:
            for symbol in symbols:
                for c in symbol:
                    if c in non_terminals:
                        first_set[nt] |= calculate_first_set(c, productions, first_set, non_terminals)
                        if 'e' not in first_set[c]:
                            break
                    else:
                        first_set[nt].add(c)
                        break
    return first_set[nt]

def first(productions, non_terminals):
    first_set = defaultdict(set)
    for nt in non_terminals:
        calculate_first_set(nt, productions, first_set, non_terminals)
    return first_set

def calculate_follow_set(nt, productions, first_set, follow_set, non_terminals, start_symbol):
    if nt == start_symbol:
        follow_set[nt].add('$')

    for production in productions:
        lhs, rhs = production
        for symbol in rhs:
            for i, c in enumerate(symbol):
                if c == nt:
                    if i == len(symbol) - 1:
                        if lhs != nt:
                            follow_set[nt] |= calculate_follow_set(lhs, productions, first_set, follow_set, non_terminals, start_symbol)
                    else:
                        next_symbol = symbol[i + 1]
                        if next_symbol in non_terminals:
                            follow_set[nt] |= first_set[next_symbol]
                            if 'e' in first_set[next_symbol]:
                                follow_set[nt] |= calculate_follow_set(next_symbol, productions, first_set, follow_set, non_terminals, start_symbol)
                        else:
                            follow_set[nt].add(next_symbol)
    
    return follow_set[nt]

def follow(productions, non_terminals, first_set, start_symbol):
    follow_set = defaultdict(set)
    for nt in non_terminals:
        calculate_follow_set(nt, productions, first_set, follow_set, non_terminals, start_symbol)
    return follow_set

# Function to create item set
def closure(items, productions):
    closure_set = set(items)
    while True:
        new_items = set(closure_set)  # Copy existing closure
        for item in closure_set:
            lhs, rhs, dot_pos = item
            if dot_pos < len(rhs):  # If dot is not at the end
                next_symbol = rhs[dot_pos]
                if next_symbol in non_terminals:  # Non-terminal found
                    for prod in productions:
                        if prod[0] == next_symbol:
                            new_item = (next_symbol, prod[1][0], 0)  # Create new item with dot at start of production
                            new_items.add(new_item)
        if new_items == closure_set:  # No new items added
            break
        closure_set = new_items
    return closure_set

def goto(items, symbol, productions):
    result = set()
    for item in items:
        lhs, rhs, dot_pos = item
        if dot_pos < len(rhs) and rhs[dot_pos] == symbol:
            new_item = (lhs, rhs, dot_pos + 1)  # Move dot to the right
            result.add(new_item)
    return closure(result, productions)

def items_table(productions, start_symbol):
    start_item = (f'${start_symbol}', productions[0][1][0], 0)  # Augmented grammar start item
    item_sets = []
    transitions = {}
    closure_set = closure({start_item}, productions)
    item_sets.append(closure_set)
    
    i = 0
    while i < len(item_sets):
        current_set = item_sets[i]
        for item in current_set:
            lhs, rhs, dot_pos = item
            if dot_pos < len(rhs):
                next_symbol = rhs[dot_pos]
                if next_symbol not in transitions:
                    transitions[(i, next_symbol)] = len(item_sets)
                    new_set = goto(current_set, next_symbol, productions)
                    if new_set and new_set not in item_sets:
                        item_sets.append(new_set)
                else:
                    # Update the transition if already exists
                    transitions[(i, next_symbol)] = transitions[(i, next_symbol)]
        i += 1
    return item_sets, transitions

# Function to construct action and GOTO tables
def construct_parsing_tables(item_sets, transitions, follow_set, start_symbol):
    action = defaultdict(dict)
    goto = defaultdict(dict)
    
    for state_index, item_set in enumerate(item_sets):
        for item in item_set:
            lhs, rhs, dot_pos = item
            
            # Check for accept condition
            if dot_pos == len(rhs) and lhs == f'${start_symbol}':
                action[state_index]['$'] = 'acc'  # Accept state

            elif dot_pos == len(rhs):  # Reduce actions
                for terminal in follow_set[lhs]:
                    action[state_index][terminal] = f'r {lhs}->{rhs}'
            else:
                next_symbol = rhs[dot_pos]
                if next_symbol in terminals:
                    action[state_index][next_symbol] = f's {transitions[(state_index, next_symbol)]}'
                elif next_symbol in non_terminals:
                    goto[state_index][next_symbol] = transitions[(state_index, next_symbol)]

    return action, goto

# Main execution starts here
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

start_symbol = productions[0][0]  # Assuming the first production's left-hand side is the start symbol

first_set = first(productions, non_terminals)

for nt in non_terminals:
    print(f"FIRST({nt}) = {{ {', '.join(first_set[nt])} }}")

print("\n-------------------------------------------------------------------\n")

follow_set = follow(productions, non_terminals, first_set, start_symbol)

for nt in non_terminals:
    if 'e' in follow_set[nt]:
        follow_set[nt].remove('e')

for nt in non_terminals:
    print(f"FOLLOW({nt}) = {{ {', '.join(follow_set[nt])} }}")

# Construct item sets and transitions
item_sets, transitions = items_table(productions, start_symbol)

# Construct parsing tables
action, goto = construct_parsing_tables(item_sets, transitions, follow_set, start_symbol)

# Print Action Table
print("\nAction Table:")
print("State\t" + "\t".join(sorted(terminals.union({'$'}))))
print("---------------------------------------------------------")
for state in range(len(item_sets)):
    row = f"{state}\t"
    for terminal in sorted(terminals.union({'$'})):
        row += f"{action[state].get(terminal, '-')} \t"
    print(row.strip())

# Print GOTO Table
print("\nGOTO Table:")
print("State\t" + "\t".join(sorted(non_terminals)))
print("---------------------------------------------------------")
for state in range(len(item_sets)):
    row = f"{state}\t"
    for non_terminal in sorted(non_terminals):
        row += f"{goto[state].get(non_terminal, '-')}\t"
    print(row.strip())
