/* 
	ETAPA 2 - TRABALHO DE COMPILADORES
	Gabriel Zillmer e Rodrigo dal Ri 
*/

#include <stdio.h>
#include <stdlib.h>

extern FILE* yyin;
extern FILE* file();
extern int yylex();
extern int isRunning();
extern int getLineNumber();
extern int yyparse();
extern void initMe();
extern void hashPrint();

int main(int argc, char *argv[]){
    int token;
	if(argc<2){
		fprintf(stderr,"Execute: ./etapa2 nomearquivo.\n");
		return 1;
	}
	if(!(file(argv[1]))){
		fprintf(stderr,"Nao eh possivel abrir o arquivo %s.\n",argv[1]);
		return 2;
	}
	
	initMe();
	
	while(isRunning()){
		yyparse();
	}	
	
	hashPrint();

	fprintf(stderr,"Parabens, Sintaxe OK!\n");

    return 0; 
}
