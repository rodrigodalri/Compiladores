etapa4: y.tab.o lex.yy.o main.o hash.o astree.o semantic.o      
	gcc -Wall y.tab.o lex.yy.o main.o hash.o astree.o semantic.o -o etapa4 
lex.yy.o: lex.yy.c
	gcc -Wall -c lex.yy.c
main.o: main.c
	gcc -Wall -c main.c
hash.o: hash.c
	gcc -Wall -c hash.c
astree.o: astree.c
	gcc -Wall -c astree.c
semantic.o: semantic.c
	gcc -Wall -c semantic.c
y.tab.o: y.tab.c	
	gcc -Wall -c y.tab.c
y.tab.c: parser.y
	yacc -d -v parser.y
lex.yy.c: scanner.l
	flex scanner.l 
clean:
	rm *.o lex.yy.c y.tab.c y.tab.h y.output etapa4


