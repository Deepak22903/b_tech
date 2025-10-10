# Scientific Calculator using Lex & Yacc

## Overview

This project implements a scientific calculator with both **ambiguous** and **unambiguous** grammar approaches.

## Components

### 1. Lexical Analyzer (calc.l)

- Tokenizes input: numbers, operators, functions, constants
- Recognizes: `+`, `-`, `*`, `/`, `^`, `%`, `(`, `)`, `,`
- Functions: `sin`, `cos`, `tan`, `log`, `ln`, `sqrt`, `exp`, `abs`, `pow`
- Constants: `pi`, `e`

### 2. Ambiguous Grammar Parser (calc_ambig.y)

**Characteristics:**

- Uses operator precedence declarations (`%left`, `%right`)
- Single non-terminal for expressions
- Relies on Yacc's precedence rules to resolve conflicts
- More concise but requires precedence specifications

**Grammar Structure:**

```
expression → expression OP expression
expression → -expression
expression → (expression)
expression → function(expression)
expression → NUMBER
```

**Precedence (lowest to highest):**

- `%left PLUS MINUS` (addition/subtraction)
- `%left TIMES DIVIDE MOD` (multiplication/division)
- `%right POWER` (exponentiation, right associative)
- `%nonassoc UMINUS` (unary minus)

### 3. Unambiguous Grammar Parser (calc_unambig.y)

**Characteristics:**

- Explicitly encodes precedence in grammar rules
- Multiple non-terminals (expression, term, factor, power, unary, primary)
- No precedence declarations needed
- More verbose but self-documenting

**Grammar Hierarchy:**

```
expression → term | expression + term | expression - term
term → factor | term * factor | term / factor | term % factor
factor → power
power → unary | unary ^ power (right associative)
unary → primary | -unary | +unary
primary → NUMBER | (expression) | function(expression)
```

## Compilation

### Requirements

- `lex` (or `flex`)
- `yacc` (or `bison`)
- `gcc`
- `math` library

### Build Instructions

```bash
# Build both versions
make all

# Build only ambiguous version
make calc_ambiguous

# Build only unambiguous version
make calc_unambiguous

# Clean generated files
make clean
```

## Usage

### Run Ambiguous Grammar Calculator

```bash
./calc_ambiguous
```

### Run Unambiguous Grammar Calculator

```bash
./calc_unambiguous
```

### Example Expressions

```
2 + 3 * 4          → 14
sin(pi/2)          → 1
sqrt(16) + 2^3     → 12
log(100)           → 2
ln(e)              → 1
pow(2, 10)         → 1024
abs(-5) * 3        → 15
(2 + 3) * 4        → 20
-5 + 3             → -2
10 % 3             → 1
```

## Key Differences

| Aspect        | Ambiguous Grammar               | Unambiguous Grammar                |
| ------------- | ------------------------------- | ---------------------------------- |
| Grammar Rules | Fewer, simpler                  | More, hierarchical                 |
| Precedence    | Declared with `%left`, `%right` | Encoded in structure               |
| Readability   | Concise                         | Self-documenting                   |
| Conflicts     | Resolved by Yacc                | None (inherent)                    |
| Maintenance   | Need to track precedence table  | Grammar structure shows precedence |

## Testing

```bash
# Test ambiguous version
make test_ambig

# Test unambiguous version
make test_unambig
```

## Operator Precedence (Highest to Lowest)

1. Unary minus (`-`)
2. Power (`^`) - right associative
3. Multiplication, Division, Modulo (`*`, `/`, `%`)
4. Addition, Subtraction (`+`, `-`)

## Error Handling

- Division by zero detection
- Invalid character detection
- Syntax error recovery

## Functions Supported

- **Trigonometric:** `sin()`, `cos()`, `tan()`
- **Logarithmic:** `log()` (base 10), `ln()` (natural)
- **Other:** `sqrt()`, `exp()`, `abs()`, `pow(base, exp)`

## Constants

- `pi` → 3.14159...
- `e` → 2.71828...

## Assignment Notes

This implementation demonstrates:

1. **Ambiguous Grammar** - resolves conflicts using precedence directives
2. **Unambiguous Grammar** - eliminates conflicts through grammar structure
3. Full scientific calculator functionality
4. Both approaches produce identical results
