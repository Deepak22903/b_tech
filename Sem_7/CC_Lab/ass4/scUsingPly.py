"""
Advanced Scientific Calculator using PLY (Python Lex-Yacc)
Features: Basic arithmetic, trigonometry, logarithms, constants, variables
"""

import ply.lex as lex
import ply.yacc as yacc
import math

# ==================== SYMBOL TABLE ====================
variables = {}
constants = {
    "pi": math.pi,
    "e": math.e,
    "tau": math.tau,
}

# ==================== LEXER ====================
tokens = (
    "NUMBER",
    "ID",
    "PLUS",
    "MINUS",
    "TIMES",
    "DIVIDE",
    "POWER",
    "MOD",
    "LPAREN",
    "RPAREN",
    "ASSIGN",
    "COMMA",
    "SIN",
    "COS",
    "TAN",
    "ASIN",
    "ACOS",
    "ATAN",
    "SINH",
    "COSH",
    "TANH",
    "LOG",
    "LN",
    "SQRT",
    "ABS",
    "EXP",
    "FLOOR",
    "CEIL",
    "FACTORIAL",
)

# Tokens as strings
t_PLUS = r"\+"
t_MINUS = r"-"
t_TIMES = r"\*"
t_DIVIDE = r"/"
t_POWER = r"\^"
t_MOD = r"%"
t_LPAREN = r"\("
t_RPAREN = r"\)"
t_ASSIGN = r"="
t_COMMA = r","
t_FACTORIAL = r"!"

# Reserved words
reserved = {
    "sin": "SIN",
    "cos": "COS",
    "tan": "TAN",
    "asin": "ASIN",
    "acos": "ACOS",
    "atan": "ATAN",
    "sinh": "SINH",
    "cosh": "COSH",
    "tanh": "TANH",
    "log": "LOG",
    "ln": "LN",
    "sqrt": "SQRT",
    "abs": "ABS",
    "exp": "EXP",
    "floor": "FLOOR",
    "ceil": "CEIL",
}


def t_ID(t):
    r"[a-zA-Z_][a-zA-Z_0-9]*"
    t.type = reserved.get(t.value, "ID")
    return t


def t_NUMBER(t):
    r"\d+\.?\d*([eE][+-]?\d+)?"
    t.value = float(t.value)
    return t


t_ignore = " \t"


def t_newline(t):
    r"\n+"
    t.lexer.lineno += len(t.value)


def t_error(t):
    print(f"Illegal character '{t.value[0]}'")
    t.lexer.skip(1)


# ==================== PARSER ====================
# Operator precedence
precedence = (
    ("left", "ASSIGN"),
    ("left", "PLUS", "MINUS"),
    ("left", "TIMES", "DIVIDE", "MOD"),
    ("right", "UMINUS", "UPLUS"),
    ("right", "POWER"),
    ("left", "FACTORIAL"),
)


def p_statement_assign(p):
    """statement : ID ASSIGN expression"""
    variables[p[1]] = p[3]
    p[0] = p[3]
    print(f"{p[1]} = {p[3]}")


def p_statement_expr(p):
    """statement : expression"""
    p[0] = p[1]


def p_expression_binop(p):
    """expression : expression PLUS expression
    | expression MINUS expression
    | expression TIMES expression
    | expression DIVIDE expression
    | expression POWER expression
    | expression MOD expression"""
    if p[2] == "+":
        p[0] = p[1] + p[3]
    elif p[2] == "-":
        p[0] = p[1] - p[3]
    elif p[2] == "*":
        p[0] = p[1] * p[3]
    elif p[2] == "/":
        if p[3] == 0:
            print("Error: Division by zero")
            p[0] = 0
        else:
            p[0] = p[1] / p[3]
    elif p[2] == "^":
        p[0] = p[1] ** p[3]
    elif p[2] == "%":
        p[0] = p[1] % p[3]


def p_expression_uminus(p):
    """expression : MINUS expression %prec UMINUS"""
    p[0] = -p[2]


def p_expression_uplus(p):
    """expression : PLUS expression %prec UPLUS"""
    p[0] = p[2]


def p_expression_factorial(p):
    """expression : expression FACTORIAL"""
    try:
        p[0] = math.factorial(int(p[1]))
    except ValueError:
        print("Error: Factorial only for non-negative integers")
        p[0] = 0


def p_expression_group(p):
    """expression : LPAREN expression RPAREN"""
    p[0] = p[2]


# Trigonometric functions (angles in degrees)
def p_expression_trig(p):
    """expression : SIN LPAREN expression RPAREN
    | COS LPAREN expression RPAREN
    | TAN LPAREN expression RPAREN"""
    if p[1] == "sin":
        p[0] = math.sin(math.radians(p[3]))
    elif p[1] == "cos":
        p[0] = math.cos(math.radians(p[3]))
    elif p[1] == "tan":
        p[0] = math.tan(math.radians(p[3]))


# Inverse trigonometric functions (return degrees)
def p_expression_invtrig(p):
    """expression : ASIN LPAREN expression RPAREN
    | ACOS LPAREN expression RPAREN
    | ATAN LPAREN expression RPAREN"""
    try:
        if p[1] == "asin":
            p[0] = math.degrees(math.asin(p[3]))
        elif p[1] == "acos":
            p[0] = math.degrees(math.acos(p[3]))
        elif p[1] == "atan":
            p[0] = math.degrees(math.atan(p[3]))
    except ValueError as e:
        print(f"Error: {e}")
        p[0] = 0


# Hyperbolic functions
def p_expression_hyper(p):
    """expression : SINH LPAREN expression RPAREN
    | COSH LPAREN expression RPAREN
    | TANH LPAREN expression RPAREN"""
    if p[1] == "sinh":
        p[0] = math.sinh(p[3])
    elif p[1] == "cosh":
        p[0] = math.cosh(p[3])
    elif p[1] == "tanh":
        p[0] = math.tanh(p[3])


# Logarithmic and exponential functions
def p_expression_log(p):
    """expression : LOG LPAREN expression RPAREN
    | LN LPAREN expression RPAREN
    | EXP LPAREN expression RPAREN"""
    try:
        if p[1] == "log":
            p[0] = math.log10(p[3])
        elif p[1] == "ln":
            p[0] = math.log(p[3])
        elif p[1] == "exp":
            p[0] = math.exp(p[3])
    except ValueError as e:
        print(f"Error: {e}")
        p[0] = 0


# Other mathematical functions
def p_expression_math(p):
    """expression : SQRT LPAREN expression RPAREN
    | ABS LPAREN expression RPAREN
    | FLOOR LPAREN expression RPAREN
    | CEIL LPAREN expression RPAREN"""
    try:
        if p[1] == "sqrt":
            p[0] = math.sqrt(p[3])
        elif p[1] == "abs":
            p[0] = abs(p[3])
        elif p[1] == "floor":
            p[0] = math.floor(p[3])
        elif p[1] == "ceil":
            p[0] = math.ceil(p[3])
    except ValueError as e:
        print(f"Error: {e}")
        p[0] = 0


def p_expression_number(p):
    """expression : NUMBER"""
    p[0] = p[1]


def p_expression_id(p):
    """expression : ID"""
    if p[1] in constants:
        p[0] = constants[p[1]]
    elif p[1] in variables:
        p[0] = variables[p[1]]
    else:
        print(f"Error: Undefined variable '{p[1]}'")
        p[0] = 0


def p_error(p):
    """Handle parsing errors"""
    if p:
        print(f"Syntax error at '{p.value}'")
    else:
        print("Syntax error at EOF")


# ==================== BUILD PARSER ====================
lexer = lex.lex()
parser = yacc.yacc()


# ==================== MAIN PROGRAM ====================
def main():
    print("=" * 60)
    print("         SCIENTIFIC CALCULATOR (PLY)")
    print("=" * 60)
    print("\nFeatures:")
    print("  • Basic: +, -, *, /, ^(power), %(mod), !(factorial)")
    print("  • Trig: sin, cos, tan, asin, acos, atan (degrees)")
    print("  • Hyperbolic: sinh, cosh, tanh")
    print("  • Log/Exp: log, ln, exp, sqrt")
    print("  • Other: abs, floor, ceil")
    print("  • Constants: pi, e, tau")
    print("  • Variables: x = 5, y = x * 2")
    print("\nExamples:")
    print("  sin(45) + cos(45)")
    print("  log(100) * ln(e)")
    print("  sqrt(16) ^ 2")
    print("  5!")
    print("  x = 10")
    print("  x * pi")
    print("\nType 'quit' or 'exit' to exit")
    print("=" * 60)

    # Demo calculations
    demo_expressions = [
        "sin(30)",
        "cos(60) + sin(30)",
        "sqrt(16) * 4",
        "log(100)",
        "5!",
        "pi * 2",
        "exp(1)",
        "abs(-10)",
    ]

    print("\nDemo Calculations:")
    for expr in demo_expressions:
        try:
            result = parser.parse(expr, lexer=lexer)
            if result is not None:
                print(f"  {expr} = {result}")
        except Exception as e:
            print(f"  Error in {expr}: {e}")

    print("\n" + "=" * 60)
    print("Interactive Mode:")
    print("=" * 60)

    while True:
        try:
            s = input("\ncalc> ")
            if s.lower() in ("quit", "exit"):
                print("Goodbye!")
                break
            if not s.strip():
                continue

            result = parser.parse(s, lexer=lexer)
            if result is not None:
                print(f"Result: {result}")

        except EOFError:
            print("\nGoodbye!")
            break
        except KeyboardInterrupt:
            print("\nGoodbye!")
            break
        except Exception as e:
            print(f"Error: {e}")


if __name__ == "__main__":
    main()
