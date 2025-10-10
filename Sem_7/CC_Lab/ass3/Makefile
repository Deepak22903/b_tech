CC = gcc
CFLAGS = -lm -ll
LEX = lex
YACC = yacc

all: calc_ambiguous calc_unambiguous

# Ambiguous Grammar Calculator
calc_ambiguous: calc_ambig.y calc.l
	$(YACC) -d calc_ambig.y
	$(LEX) calc.l
	$(CC) y.tab.c lex.yy.c -o calc_ambiguous $(CFLAGS)
	@echo "Built: calc_ambiguous"

# Unambiguous Grammar Calculator
calc_unambiguous: calc_unambig.y calc.l
	$(YACC) -d calc_unambig.y
	$(LEX) calc.l
	$(CC) y.tab.c lex.yy.c -o calc_unambiguous $(CFLAGS)
	@echo "Built: calc_unambiguous"

clean:
	rm -f calc_ambiguous calc_unambiguous y.tab.c y.tab.h lex.yy.c

test_ambig: calc_ambiguous
	@echo "Testing ambiguous grammar calculator..."
	@echo "2 + 3 * 4" | ./calc_ambiguous
	@echo "sin(pi/2)" | ./calc_ambiguous
	@echo "sqrt(16) + 2^3" | ./calc_ambiguous

test_unambig: calc_unambiguous
	@echo "Testing unambiguous grammar calculator..."
	@echo "2 + 3 * 4" | ./calc_unambiguous
	@echo "sin(pi/2)" | ./calc_unambiguous
	@echo "sqrt(16) + 2^3" | ./calc_unambiguous

.PHONY: all clean test_ambig test_unambig
