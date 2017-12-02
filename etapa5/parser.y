/* 
	ETAPA 5 - TRABALHO DE COMPILADORES
	Gabriel Zillmer e Rodrigo dal Ri 
*/

%{
	
	#include <stdio.h>
	#include <stdlib.h>

	#include "astree.h"
	#include "hash.h"
	#include "semantic.h"	
	#include "tac.h"
	
		
	int yylex();
	int yyerror(char *message);
	extern int getLineNumber();
	int erro;

	ASTREE *root;
%}


%union{
	Hash_Node *symbol;
	ASTREE *astree;
}


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

%token <symbol> TK_IDENTIFIER
%token <symbol> LIT_INTEGER
%token <symbol> LIT_REAL
%token <symbol> LIT_CHAR
%token <symbol> LIT_STRING

%token TOKEN_ERROR 

%left '<' '>'  
%left '!' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE OPERATOR_AND OPERATOR_OR
%left '+' '-'
%left '*' '/'

%start prog

%type <astree>listadeclaracoes
%type <astree>declaracoes
%type <astree>init
%type <astree>bloco
%type <astree>cmdbloco
%type <astree>cmdfim
%type <astree>cmd
%type <astree>exp
%type <astree>tipo
%type <astree>literal
%type <astree>printaveis
%type <astree>listaparametros
%type <astree>listaparametroscall
%type <astree>parametrosfim
%type <astree>parametrosfim2
%type <astree>parametro

%type <astree>prog

%%



prog : listadeclaracoes { root = $$; 
			  astreePrint(0, root);  
			  erro = checkSemantic(root);
			  tacPrintFoward(tacReverse(tacGenerate($1)));
			}
     ;

listadeclaracoes : declaracoes listadeclaracoes			{ $$ = astreeCreate(ASTREE_DFNL, 0, $1, $2, 0, 0); }
	         |						{ $$ = 0; }
                 ;

declaracoes : TK_IDENTIFIER ':' tipo '=' literal ';'			{ $$ = astreeCreate(ASTREE_VARINI, $1, $3, $5, 0, 0); } 
	    | TK_IDENTIFIER ':' tipo '[' LIT_INTEGER ']' init ';'	{ $$ = astreeCreate(ASTREE_ARRINI, $1, $3, astreeCreate(ASTREE_SYMBOL, $5, 0, 0, 0, 0), $7, 0); } 
	    | '(' tipo ')' TK_IDENTIFIER '(' listaparametros ')' bloco  { $$ = astreeCreate(ASTREE_FUNDEF, $4, $2, $6, $8, 0); } 
	    ;

init : literal init				{ $$ = astreeCreate(ASTREE_INTL, 0, $1, $2, 0, 0); }
     |						{ $$ = 0; }
     ;

bloco : '{' cmdbloco '}'			{ $$ = astreeCreate(ASTREE_BRACES, 0, $2, 0, 0, 0);   }
      ;

cmdbloco : cmd cmdfim				{ $$ = astreeCreate(ASTREE_CMDL, 0, $1, $2, 0, 0); }
	 ;

cmdfim : ';' cmd cmdfim 			{ $$ = astreeCreate(ASTREE_CMDL, 0, $2, $3, 0, 0); }
       |					{ $$ = 0; }
       ;

cmd : TK_IDENTIFIER '=' exp			{ $$ = astreeCreate(ASTREE_ATR, $1, $3, 0, 0, 0); }
    | TK_IDENTIFIER '[' exp ']' '=' exp		{ $$ = astreeCreate(ASTREE_ARRAY_WRITE,$1, $3, $6, 0, 0); }				
    | KW_IF '(' exp ')' KW_THEN cmd      	{ $$ = astreeCreate(ASTREE_IF, 0, $3, $6, 0, 0); }
    | KW_IF '(' exp ')' KW_THEN cmd KW_ELSE cmd { $$ = astreeCreate(ASTREE_ELSE, 0, $3, $6, $8, 0); }
    | KW_WHILE '(' exp ')' cmd 			{ $$ = astreeCreate(ASTREE_WHILE, 0, $3, $5, 0, 0); }
    | KW_PRINT printaveis 			{ $$ = astreeCreate(ASTREE_PRINT, 0, $2, 0, 0, 0); }
    | KW_READ '>' TK_IDENTIFIER			{ $$ = astreeCreate(ASTREE_READ, $3, 0, 0, 0, 0); }
    | KW_RETURN exp 				{ $$ = astreeCreate(ASTREE_RETURN, 0, $2, 0, 0, 0); }
    | bloco 					{ $$ = $1; }
    |						{ $$ = 0; }
    ;

exp : TK_IDENTIFIER 				{ $$ = astreeCreate(ASTREE_SYMBOL, $1, 0, 0, 0, 0); }
    | TK_IDENTIFIER '[' exp ']' 		{ $$ = astreeCreate(ASTREE_ARRAY_READ, $1, $3, 0, 0, 0); }
    | TK_IDENTIFIER '(' listaparametroscall ')' 	{ $$ = astreeCreate(ASTREE_FUNCALL, $1, $3, 0, 0, 0); }
    | literal					{$$ = $1;}
    | LIT_STRING				{ $$ = astreeCreate(ASTREE_SYMBOL, $1, 0, 0, 0, 0); }
    | exp '+' exp				{ $$ = astreeCreate(ASTREE_ADD, 0, $1, $3, 0, 0); }
    | exp '-' exp 				{ $$ = astreeCreate(ASTREE_SUB, 0, $1, $3, 0, 0); }
    | exp '*' exp 				{ $$ = astreeCreate(ASTREE_MUL, 0, $1, $3, 0, 0); }
    | exp '/' exp 				{ $$ = astreeCreate(ASTREE_DIV, 0, $1, $3, 0, 0); }
    | exp '<' exp 				{ $$ = astreeCreate(ASTREE_L, 0, $1, $3, 0, 0); }
    | exp '>' exp 				{ $$ = astreeCreate(ASTREE_G, 0, $1, $3, 0, 0); }
    | '!' exp					{ $$ = astreeCreate(ASTREE_NOT, 0, $2, 0, 0, 0); }
    | exp OPERATOR_LE exp			{ $$ = astreeCreate(ASTREE_LE, 0, $1, $3, 0, 0); }
    | exp OPERATOR_GE exp 			{ $$ = astreeCreate(ASTREE_GE, 0, $1, $3, 0, 0); }
    | exp OPERATOR_EQ exp			{ $$ = astreeCreate(ASTREE_EQ, 0, $1, $3, 0, 0); }
    | exp OPERATOR_NE exp			{ $$ = astreeCreate(ASTREE_NE, 0, $1, $3, 0, 0); }
    | exp OPERATOR_AND exp			{ $$ = astreeCreate(ASTREE_AND, 0, $1, $3, 0, 0); }
    | exp OPERATOR_OR exp			{ $$ = astreeCreate(ASTREE_OR, 0, $1, $3, 0, 0); }
    | '(' exp ')'				{ $$ = astreeCreate(ASTREE_PARENTHESIS, 0, $2, 0, 0, 0);   }
    ;

tipo : KW_BYTE			{ $$ = astreeCreate(ASTREE_BYTE, 0, 0, 0, 0, 0); }
     | KW_SHORT			{ $$ = astreeCreate(ASTREE_SHORT, 0, 0, 0, 0, 0); }
     | KW_LONG			{ $$ = astreeCreate(ASTREE_LONG, 0, 0, 0, 0, 0); }
     | KW_FLOAT			{ $$ = astreeCreate(ASTREE_FLOAT, 0, 0, 0, 0, 0); }
     | KW_DOUBLE		{ $$ = astreeCreate(ASTREE_DOUBLE, 0, 0, 0, 0, 0); }
     ;

literal : LIT_CHAR 		{ $$ = astreeCreate(ASTREE_SYMBOL, $1, 0, 0, 0, 0); }
	| LIT_INTEGER		{ $$ = astreeCreate(ASTREE_SYMBOL, $1, 0, 0, 0, 0); }
	| LIT_REAL		{ $$ = astreeCreate(ASTREE_SYMBOL, $1, 0, 0, 0, 0); }
	;

printaveis : exp ',' printaveis		{ $$ = astreeCreate(ASTREE_PRINTL, 0, $1, $3, 0, 0); } 
	   | exp				{ $$ = astreeCreate(ASTREE_PRINTL, 0, $1, 0, 0, 0); } 
	   ;

listaparametros : parametro parametrosfim       { $$ = astreeCreate(ASTREE_PARL, 0, $1, $2, 0, 0); }  
                | 				{ $$ = 0; }
                ;

parametrosfim : ',' parametro parametrosfim     { $$ = astreeCreate(ASTREE_PARL, 0, $2, $3, 0, 0); }  
	      | 				{ $$ = 0; }	
	      ;

listaparametroscall :  parametro parametrosfim2   { $$ = astreeCreate(ASTREE_PARCALLL, 0, $1, $2, 0, 0); }		
		    | 				   { $$ = 0; }
		    ;

parametrosfim2 : ',' parametro parametrosfim2     { $$ = astreeCreate(ASTREE_PARCALLL, 0, $2, $3, 0, 0); }  
	      | 				{ $$ = 0; }	
	      ;


parametro : TK_IDENTIFIER ':' tipo 	{ $$ = astreeCreate(ASTREE_PARAM, $1, $3, 0, 0, 0); } 
          | exp
	  ;
%%

ASTREE* getAst()
{
	return root;
}

void resultSemantic()
{	
	if(erro > 0)
	{
		fprintf(stderr, "%d erros semanticos.\n", erro);
		exit(4);
	}
}

int yyerror(char *err)
{
	fprintf(stderr, "ERRO Parser. Linha = %d\n", getLineNumber());
	exit(3);
}
