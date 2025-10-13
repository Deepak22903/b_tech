"""
Scientific Calculator using PLY (Python Lex-Yacc)
Includes both ambiguous and unambiguous grammar versions
"""

import ply.lex as lex
import ply.yacc as yacc
import math

# ==================== LEXER ====================
tokens = (
    "NUMBER",
    "PLUS",
    "MINUS",
    "TIMES",
    "DIVIDE",
    "POWER",
    "LPAREN",
    "RPAREN",
    "SIN",
    "COS",
    "TAN",
    "LOG",
    "SQRT",
)

t_PLUS = r"\+"
t_MINUS = r"-"
t_TIMES = r"\*"
t_DIVIDE = r"/"
t_POWER = r"\^"
t_LPAREN = r"\("
t_RPAREN = r"\)"
t_ignore = " \t"


def t_SIN(t):
    r"sin"
    return t


def t_COS(t):
    r"cos"
    return t


def t_TAN(t):
    r"tan"
    return t


def t_LOG(t):
    r"log"
    return t


def t_SQRT(t):
    r"sqrt"
    return t


def t_NUMBER(t):
    r"\d+(\.\d+)?"
    t.value = float(t.value)
    return t


def t_newline(t):
    r"\n+"
    t.lexer.lineno += len(t.value)


def t_error(t):
    print(f"Illegal character '{t.value[0]}'")
    t.lexer.skip(1)


# ==================== AMBIGUOUS GRAMMAR PARSER ====================
print("=" * 50)
print("AMBIGUOUS GRAMMAR VERSION")
print("=" * 50)

# Precedence rules to resolve ambiguity
precedence_ambiguous = (
    ("left", "PLUS", "MINUS"),
    ("left", "TIMES", "DIVIDE"),
    ("right", "POWER"),
)


def p_expr_binop_ambiguous(p):
    """expr : expr PLUS expr
    | expr MINUS expr
    | expr TIMES expr
    | expr DIVIDE expr
    | expr POWER expr"""
    if p[2] == "+":
        p[0] = p[1] + p[3]
    elif p[2] == "-":
        p[0] = p[1] - p[3]
    elif p[2] == "*":
        p[0] = p[1] * p[3]
    elif p[2] == "/":
        p[0] = p[1] / p[3]
    elif p[2] == "^":
        p[0] = p[1] ** p[3]


def p_expr_func_ambiguous(p):
    """expr : SIN LPAREN expr RPAREN
    | COS LPAREN expr RPAREN
    | TAN LPAREN expr RPAREN
    | LOG LPAREN expr RPAREN
    | SQRT LPAREN expr RPAREN"""
    if p[1] == "sin":
        p[0] = math.sin(math.radians(p[3]))
    elif p[1] == "cos":
        p[0] = math.cos(math.radians(p[3]))
    elif p[1] == "tan":
        p[0] = math.tan(math.radians(p[3]))
    elif p[1] == "log":
        p[0] = math.log10(p[3])
    elif p[1] == "sqrt":
        p[0] = math.sqrt(p[3])


def p_expr_paren_ambiguous(p):
    "expr : LPAREN expr RPAREN"
    p[0] = p[2]


def p_expr_number_ambiguous(p):
    "expr : NUMBER"
    p[0] = p[1]


def p_error(p):
    """Handle parsing errors"""
    if p:
        print(f"Syntax error at '{p.value}'")
    else:
        print("Syntax error at EOF")


# Build ambiguous parser
lexer_ambiguous = lex.lex()
parser_ambiguous = yacc.yacc()

# Test ambiguous grammar
test_cases = [
    "3 + 5 * 2",
    "10 - 2 ^ 3",
    "sin(30) + cos(60)",
    "sqrt(16) * 4",
    "(5 + 3) * 2",
]

print("\nTesting Ambiguous Grammar:")
print("(Uses precedence rules to resolve conflicts)")
for expr in test_cases:
    result = parser_ambiguous.parse(expr, lexer=lexer_ambiguous)
    print(f"{expr} = {result}")

# ==================== UNAMBIGUOUS GRAMMAR PARSER ====================
print("\n" + "=" * 50)
print("UNAMBIGUOUS GRAMMAR VERSION")
print("=" * 50)

# Clear previous definitions
import sys

module = sys.modules[__name__]
for name in dir(module):
    if name.startswith("p_") and name not in ["p_error"]:
        delattr(module, name)

# Unambiguous grammar with explicit precedence hierarchy
# expr -> term -> factor -> power -> atom


def p_expression(p):
    """expr : expr PLUS term
    | expr MINUS term"""
    if p[2] == "+":
        p[0] = p[1] + p[3]
    else:
        p[0] = p[1] - p[3]


def p_expression_term(p):
    """expr : term"""
    p[0] = p[1]


def p_term_mult(p):
    """term : term TIMES factor
    | term DIVIDE factor"""
    if p[2] == "*":
        p[0] = p[1] * p[3]
    else:
        p[0] = p[1] / p[3]


def p_term_factor(p):
    """term : factor"""
    p[0] = p[1]


def p_factor_power(p):
    """factor : power POWER factor"""
    p[0] = p[1] ** p[3]


def p_factor_atom(p):
    """factor : power"""
    p[0] = p[1]


def p_power_atom(p):
    """power : atom"""
    p[0] = p[1]


def p_atom_number(p):
    """atom : NUMBER"""
    p[0] = p[1]


def p_atom_paren(p):
    """atom : LPAREN expr RPAREN"""
    p[0] = p[2]


def p_atom_function(p):
    """atom : SIN LPAREN expr RPAREN
    | COS LPAREN expr RPAREN
    | TAN LPAREN expr RPAREN
    | LOG LPAREN expr RPAREN
    | SQRT LPAREN expr RPAREN"""
    if p[1] == "sin":
        p[0] = math.sin(math.radians(p[3]))
    elif p[1] == "cos":
        p[0] = math.cos(math.radians(p[3]))
    elif p[1] == "tan":
        p[0] = math.tan(math.radians(p[3]))
    elif p[1] == "log":
        p[0] = math.log10(p[3])
    elif p[1] == "sqrt":
        p[0] = math.sqrt(p[3])


# Build unambiguous parser (no precedence needed!)
lexer_unambiguous = lex.lex()
parser_unambiguous = yacc.yacc()

print("\nTesting Unambiguous Grammar:")
print("(No precedence rules needed - grammar structure defines precedence)")
for expr in test_cases:
    result = parser_unambiguous.parse(expr, lexer=lexer_unambiguous)
    print(f"{expr} = {result}")

print("\n" + "=" * 50)
print("INTERACTIVE MODE (Unambiguous Grammar)")
print("=" * 50)
print("Enter expressions (or 'quit' to exit):")
print("Examples: 3+5*2, sin(45), sqrt(16)^2\n")

while True:
    try:
        s = input("calc> ")
        if s.lower() == "quit":
            break
        if not s:
            continue
        result = parser_unambiguous.parse(s, lexer=lexer_unambiguous)
        print(f"Result: {result}")
    except EOFError:
        break
    except Exception as e:
        print(f"Error: {e}")
