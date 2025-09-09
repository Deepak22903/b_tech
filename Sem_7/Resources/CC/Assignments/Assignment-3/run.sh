flex calc.l
yacc calc.y
gcc lex.yy.c y.tab.c -o calculator -lm
./calculator