# scientific_calculator.py

import math
import ply.lex as lex
import ply.yacc as yacc

## ------------------- LEXER (TOKENIZER) ------------------- ##

# Dictionary to store variable names
names = {}

# List of token names. This is always required.
tokens = (
    "NAME",
    "NUMBER",
    "PLUS",
    "MINUS",
    "TIMES",
    "DIVIDE",
    "POWER",
    "LPAREN",
    "RPAREN",
    "EQUALS",
)

# Regular expression rules for simple tokens
t_PLUS = r"\+"
t_MINUS = r"-"
t_TIMES = r"\*"
t_DIVIDE = r"/"
t_POWER = r"\^"
t_LPAREN = r"\("
t_RPAREN = r"\)"
t_EQUALS = r"="

# A string containing ignored characters (spaces and tabs)
t_ignore = " \t"


# A rule to handle numbers (including floating point)
def t_NUMBER(t):
    r"\d*\.?\d+"
    t.value = float(t.value)
    return t


# A rule to handle names (variables, constants, and functions)
def t_NAME(t):
    r"[a-zA-Z_][a-zA-Z_0-9]*"
    # Check for built-in constants and functions
    t.type = "NAME"
    return t


# Define a rule so we can track line numbers
def t_newline(t):
    r"\n+"
    t.lexer.lineno += len(t.value)


# Error handling rule for illegal characters
def t_error(t):
    print(f"Illegal character '{t.value[0]}'")
    t.lexer.skip(1)


# Build the lexer
lexer = lex.lex()


## ------------------- PARSER (GRAMMAR & EVALUATION) ------------------- ##

# Define operator precedence and associativity
precedence = (
    ("left", "PLUS", "MINUS"),
    ("left", "TIMES", "DIVIDE"),
    ("right", "UMINUS"),  # Unary minus precedence
    ("right", "POWER"),
)

# --- Grammar Rules ---


def p_statement_assign(p):
    "statement : NAME EQUALS expression"
    names[p[1]] = p[3]
    p[0] = p[3]


def p_statement_expr(p):
    "statement : expression"
    print(p[1])
    p[0] = p[1]


def p_expression_binop(p):
    """expression : expression PLUS expression
    | expression MINUS expression
    | expression TIMES expression
    | expression DIVIDE expression
    | expression POWER expression"""
    if p[2] == "+":
        p[0] = p[1] + p[3]
    elif p[2] == "-":
        p[0] = p[1] - p[3]
    elif p[2] == "*":
        p[0] = p[1] * p[3]
    elif p[2] == "/":
        if p[3] == 0:
            print("Error: Division by zero")
            p[0] = 0  # Or handle error appropriately
        else:
            p[0] = p[1] / p[3]
    elif p[2] == "^":
        p[0] = math.pow(p[1], p[3])


def p_expression_uminus(p):
    "expression : MINUS expression %prec UMINUS"
    p[0] = -p[2]


def p_expression_group(p):
    "expression : LPAREN expression RPAREN"
    p[0] = p[2]


def p_expression_number(p):
    "expression : NUMBER"
    p[0] = p[1]


def p_expression_name(p):
    "expression : NAME"
    try:
        # Check for predefined constants
        if p[1] == "pi":
            p[0] = math.pi
        elif p[1] == "e":
            p[0] = math.e
        else:
            # Look it up in the names dictionary
            p[0] = names[p[1]]
    except LookupError:
        print(f"Undefined name '{p[1]}'")
        p[0] = 0


def p_expression_func_call(p):
    "expression : NAME LPAREN expression RPAREN"
    # Mapping function names to math module functions
    func_map = {
        "sin": math.sin,
        "cos": math.cos,
        "tan": math.tan,
        "sqrt": math.sqrt,
        "exp": math.exp,
        "log": math.log,
        "log10": math.log10,
    }
    if p[1] in func_map:
        # Convert degrees to radians for trig functions if needed
        if p[1] in ["sin", "cos", "tan"]:
            p[0] = func_map[p[1]](math.radians(p[3]))
        else:
            p[0] = func_map[p[1]](p[3])
    else:
        print(f"Error: Unknown function '{p[1]}'")
        p[0] = 0


# Error rule for syntax errors
def p_error(p):
    if p:
        print(f"Syntax error at '{p.value}'")
    else:
        print("Syntax error at EOF")


# Build the parser
parser = yacc.yacc()


## ------------------- MAIN DRIVER ------------------- ##

print("--- Scientific Calculator ---")
print("Enter 'exit' to quit.")

while True:
    try:
        s = input("calc > ")
    except EOFError:
        break
    if not s or s.lower() == "exit":
        break
    parser.parse(s)
