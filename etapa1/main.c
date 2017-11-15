/* 
	ETAPA 1 - TRABALHO DE COMPILADORES
	Gabriel Zillmer e Rodrigo dal Ri 
*/

#include <stdio.h>
#include "tokens.h"

extern FILE* yyin;
extern FILE* file();
extern int yylex();
extern int isRunning();
extern int getLineNumber();
extern void initMe();
extern void hashPrint();

int main(int argc, char *argv[]){
    int token;
	if(argc<2){
		fprintf(stderr,"Execute: ./etapa1 nomearquivo.\n");
		return 1;
	}
	if(!(file(argv[1]))){
		fprintf(stderr,"Nao eh possivel abrir o arquivo %s.\n",argv[1]);
		return 2;
	}

	initMe();

	while(isRunning()){
		token = yylex();
		if(!isRunning()) break;
		switch(token){
            		case KW_BYTE:		fprintf(stderr, "KW_BYTE na linha %d. - tok = %d \n", getLineNumber(),KW_BYTE); break;
            		case KW_SHORT:		fprintf(stderr, "KW_SHORT na linha %d. - tok = %d \n", getLineNumber(),KW_SHORT); break;
          		case KW_LONG:		fprintf(stderr, "KW_LONG na linha %d. - tok = %d \n", getLineNumber(),KW_LONG); break;
            		case KW_FLOAT:		fprintf(stderr, "KW_FLOAT na linha %d. - tok = %d \n", getLineNumber(),KW_FLOAT); break;
            		case KW_DOUBLE:		fprintf(stderr, "KW_DOUBLE na linha %d. - tok = %d \n", getLineNumber(),KW_DOUBLE); break;
            		case KW_IF:		fprintf(stderr, "KW_IF na linha %d. - tok = %d \n", getLineNumber(),KW_IF); break;
            		case KW_THEN:		fprintf(stderr, "KW_THEN na linha %d. - tok = %d \n", getLineNumber(),KW_THEN); break;
            		case KW_ELSE:		fprintf(stderr, "KW_ELSE na linha %d. - tok = %d \n", getLineNumber(),KW_ELSE); break;
            		case KW_WHILE:		fprintf(stderr, "KW_WHILE na linha %d. - tok = %d \n", getLineNumber(),KW_WHILE); break;
            		case KW_FOR:		fprintf(stderr, "KW_FOR na linha %d. - tok = %d \n", getLineNumber(),KW_FOR); break;
            		case KW_READ:		fprintf(stderr, "KW_READ na linha %d. - tok = %d \n", getLineNumber(),KW_READ); break;
            		case KW_RETURN:		fprintf(stderr, "KW_RETURN na linha %d. - tok = %d \n", getLineNumber(),KW_RETURN); break;
            		case KW_PRINT:		fprintf(stderr, "KW_PRINT na linha %d. - tok = %d \n", getLineNumber(),KW_PRINT); break;
            		case OPERATOR_LE:	fprintf(stderr, "OPERATOR_LE na linha %d. - tok = %d \n", getLineNumber(),OPERATOR_LE); break;
            		case OPERATOR_GE:	fprintf(stderr, "OPERATOR_GE na linha %d. - tok = %d \n", getLineNumber(),OPERATOR_GE); break;
            		case OPERATOR_EQ:	fprintf(stderr, "OPERATOR_EQ na linha %d. - tok = %d \n", getLineNumber(),OPERATOR_EQ); break;
            		case OPERATOR_NE:	fprintf(stderr, "OPERATOR_NE na linha %d. - tok = %d \n", getLineNumber(),OPERATOR_NE); break;
            		case OPERATOR_AND:	fprintf(stderr, "OPERATOR_AND na linha %d. - tok = %d \n", getLineNumber(),OPERATOR_AND); break;
            		case OPERATOR_OR:	fprintf(stderr, "OPERATOR_OR na linha %d. - tok = %d \n", getLineNumber(),OPERATOR_OR); break;
            		case TK_IDENTIFIER:	fprintf(stderr, "TK_IDENTIFIER na linha %d. - tok = %d \n", getLineNumber(),TK_IDENTIFIER); break;
            		case LIT_INTEGER:	fprintf(stderr, "LIT_INTEGER na linha %d. - tok = %d \n", getLineNumber(),LIT_INTEGER); break;
            		case LIT_REAL:		fprintf(stderr, "LIT_REAL na linha %d. - tok = %d \n", getLineNumber(),LIT_REAL); break;
            		case LIT_CHAR:		fprintf(stderr, "LIT_CHAR na linha %d. - tok = %d \n", getLineNumber(),LIT_CHAR); break;
            		case LIT_STRING:	fprintf(stderr, "LIT_STRING na linha %d. - tok = %d \n", getLineNumber(),LIT_STRING); break;
            		case TOKEN_ERROR:	fprintf(stderr, "TOKEN_ERROR na linha %d. - tok = %d \n", getLineNumber(),TOKEN_ERROR); break;
            		default:		fprintf(stderr, "CARACTER ESPECIAL na linha %d. - tok = %d \n", getLineNumber(),token); break;
		}
	}	
	
	hashPrint();

    return 0; 
}
