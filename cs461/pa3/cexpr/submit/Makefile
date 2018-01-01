cexpr: y.tab.c lex.yy.c
	gcc -g -o cexpr y.tab.c lex.yy.c -ll

y.tab.c: cexpr.y
	yacc -d cexpr.y

lex.yy.c: scan.l
	lex scan.l

clean:
	rm -f y.tab.c y.tab.h lex.yy.c cexpr
