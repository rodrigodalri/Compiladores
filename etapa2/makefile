etapa2: y.tab.o lex.yy.o hash.o main.o 
	gcc y.tab.o lex.yy.o hash.o main.o -o etapa2 
main.o: main.c
	gcc -c main.c
hash.o: hash.c
	gcc -c hash.c
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: scanner.l
	flex scanner.l 
y.tab.o: y.tab.c	
	gcc -c y.tab.c
y.tab.c: parser.y
	yacc -d -v parser.y
clean:
	rm *.o lex.yy.c y.tab.c y.tab.h y.output etapa2


