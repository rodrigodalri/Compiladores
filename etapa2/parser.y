/* 
	ETAPA 2 - TRABALHO DE COMPILADORES
	Gabriel Zillmer e Rodrigo dal Ri 
*/

%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "hash.h"
	
	int yylex();
	int yyerror(char *message);
	extern int getLineNumber();

%}

%token KW_BYTE
%token KW_SHORT
%token KW_LONG
%token KW_FLOAT
%token KW_DOUBLE
%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_FOR
%token KW_READ
%token KW_RETURN
%token KW_PRINT

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_NE
%token OPERATOR_AND
%token OPERATOR_OR

%token TK_IDENTIFIER
%token LIT_INTEGER
%token LIT_REAL
%token LIT_CHAR
%token LIT_STRING

%token TOKEN_ERROR 

%left '<' '>'  
%left '!' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE OPERATOR_AND OPERATOR_OR
%left '+' '-'
%left '*' '/'

%start prog

%%



prog : listadeclaracoes
     ;

listadeclaracoes : declaracoes listadeclaracoes
	         |
                 ;

declaracoes : TK_IDENTIFIER ':' tipo '=' literal ';'
	    | TK_IDENTIFIER ':' tipo '[' LIT_INTEGER ']' init ';'
	    | '(' tipo ')' TK_IDENTIFIER '(' listaparametros ')' bloco
	    ;

init : literal init
     |
     ;

bloco : '{' cmdbloco '}'
      ;

cmdbloco : cmd cmdfim
	 ;

cmdfim : ';' cmd cmdfim 
       |
       ;

cmd : TK_IDENTIFIER '=' expressao
    | TK_IDENTIFIER '[' expressao ']' '=' expressao
    | KW_IF '(' expressao ')' KW_THEN cmd else 
    | KW_WHILE '(' expressao ')' cmd 
    | KW_PRINT printaveis 
    | KW_READ '>' TK_IDENTIFIER
    | KW_RETURN expressao 
    | bloco 
    |
    ;

else : KW_ELSE cmd 
     |
     ;

expressao : TK_IDENTIFIER 
    | TK_IDENTIFIER '[' expressao ']' 
    | TK_IDENTIFIER '(' listaparametros ')' 
    | literal
    | LIT_STRING
    | expressao '+' expressao 
    | expressao '-' expressao 
    | expressao '*' expressao 
    | expressao '/' expressao
    | expressao '<' expressao
    | expressao '>' expressao 
    | '!' '(' expressao ')'
    | expressao OPERATOR_LE expressao
    | expressao OPERATOR_GE expressao 
    | expressao OPERATOR_EQ expressao
    | expressao OPERATOR_NE expressao
    | expressao OPERATOR_AND expressao
    | expressao OPERATOR_OR expressao
    | '(' expressao ')'
    ;

tipo : KW_BYTE
     | KW_SHORT
     | KW_LONG
     | KW_FLOAT
     | KW_DOUBLE
     ;

literal : LIT_CHAR
	| LIT_INTEGER
	| LIT_REAL
	;

printaveis : expressao fimprintaveis
	   ;

fimprintaveis : ',' expressao fimprintaveis 
	      |
	      ; 

listaparametros : parametro parametrosfim 
                | 
                ;

parametrosfim : ',' parametro parametrosfim 
	      | 	
	      ;

parametro : TK_IDENTIFIER ':' tipo 
          | TK_IDENTIFIER 
          | literal
          | LIT_STRING
          ;
%%

int yyerror(char *err){
	
	fprintf(stderr, "Problema! ERRO linha = %d\n", getLineNumber());
	exit(3);
}
