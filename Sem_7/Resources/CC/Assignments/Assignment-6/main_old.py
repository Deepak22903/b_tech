import re
from collections import defaultdict

# Function to read the CFG file and return a list of production rules
def read_productions(file_path):
    productions = []
    
    # Read the file line by line
    with open(file_path, 'r') as file:
        for line in file:
            line = line.strip()
            if line:
                productions.append(line)
    
    return productions

# Function to extract non-terminals from the list of productions
def extract_non_terminals(productions):
    non_terminals = set()

    # Regular expression to match non-terminals (Assuming they are uppercase or contain a single quote)
    non_terminal_pattern = re.compile(r"[A-Z]'+?|\b[A-Z]\b")

    for production in productions:
        # Split the production at '->' to separate the non-terminal from the rules
        non_terminal, _ = production.split('->')
        # Strip whitespace and add the non-terminal to the set
        non_terminal = non_terminal.strip()
        non_terminals.add(non_terminal)

    return non_terminals

# Function to extract terminals from the list of productions
def extract_terminals(productions, non_terminals):
    terminals = set()

    # Regular expression to match potential terminals (everything except non-terminals and special characters)
    terminal_pattern = re.compile(r"[a-z]+|[+\-*/()]|id|e")  # 'e' represents epsilon

    for production in productions:
        # Split the production at '->' to get the production rules
        _, rules = production.split('->')
        
        # Remove special characters and strip whitespace
        rules = rules.replace('|', ' ').strip()

        # Find all terminals in the production rules
        symbols = rules.split()
        for symbol in symbols:
            if symbol not in non_terminals:
                matches = terminal_pattern.findall(symbol)
                for match in matches:
                    terminals.add(match)

    return terminals

# Main execution
file_path = 'grammar.txt'

# Step 1: Read the file and get the list of productions
productions = read_productions(file_path)

# Step 2: Extract non-terminals
non_terminals = extract_non_terminals(productions)

# Step 3: Extract terminals
terminals = extract_terminals(productions, non_terminals)

# Display the results
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
        lhs, rhs = production.split('->')
        if lhs.strip() == nt:
            symbols = rhs.split('|')
            for symbol in symbols:
                if symbol.strip() == 'e':
                    first_set[nt].add('e')
                else:
                    if symbol[0] in non_terminals:
                        first_set[nt] |= calculate_first_set(symbol[0])
                    else:
                        # first_set[nt].add(symbol[0])
                        c=''
                        for i in symbol:
                            if i=='|' or i.isupper() or i=='e':
                                break
                            c+=i
                        first_set[nt].add(c)
    
    return first_set[nt]

# Calculate the FIRST set for each non-terminal
for nt in non_terminals:
    calculate_first_set(nt)

# Display the FIRST sets
for nt in non_terminals:
    print(f"FIRST({nt}) = {{ {', '.join(first_set[nt])} }}")


print("\n-------------------------------------------------------------------\n")

follow_set = defaultdict(set)

def calculate_follow_set(nt):
    if nt == 'E':
        follow_set[nt].add('$')
    
    for production in productions:
        lhs, rhs = production.split('->')
        symbols = rhs.split('|')
        for symbol in symbols:
            if nt in symbol:
                idx = symbol.index(nt)
                if '\'' not in nt and (idx<len(symbol)-1 and symbol[idx+1]!="'"): 
                    if idx == len(symbol) - 1:
                        if lhs != nt:
                            follow_set[nt] |= calculate_follow_set(lhs)
                    else:
                        if symbol[idx + 1] != "\'":
                            next_symbol = symbol[idx + 1]
                            if next_symbol in non_terminals:
                                follow_set[nt] |= first_set[next_symbol]
                                if 'e' in first_set[next_symbol]:
                                    follow_set[nt] |= calculate_follow_set(next_symbol)
                            else:
                                if next_symbol != 'e':
                                    follow_set[nt].add(next_symbol)
                else:
                    idx+=1
                    if idx == len(symbol):
                        if lhs != nt:
                            follow_set[nt] |= calculate_follow_set(lhs)
                    else:
                        next_symbol = symbol[idx]
                        if next_symbol in non_terminals:
                            follow_set[nt] |= first_set[next_symbol]
                            if 'e' in first_set[next_symbol]:
                                follow_set[nt] |= calculate_follow_set(next_symbol)
                        else:
                            if next_symbol != 'e':
                                follow_set[nt].add(next_symbol)
                           
    
    return follow_set[nt]


# Calculate the FOLLOW set for each non-terminal
for nt in non_terminals:
    calculate_follow_set(nt)

# Remove 'e' from the FOLLOW sets
for nt in non_terminals:
    if 'e' in follow_set[nt]:
        follow_set[nt].remove('e')

# Display the FOLLOW sets
for nt in non_terminals:
    print(f"FOLLOW({nt}) = {{ {', '.join(follow_set[nt])} }}")

