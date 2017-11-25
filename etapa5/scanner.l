/* 
	ETAPA 5 - TRABALHO DE COMPILADORES
	Gabriel Zillmer e Rodrigo dal Ri
*/

%{

	#include "hash.h"
	#include "astree.h"
	#include "y.tab.h"
        
	int lineNumber = 1;
    	int running = 1;  
   	int yyparse(); 
%}

%x COMMENT

%%

"byte"  {return KW_BYTE;}
"short" {return KW_SHORT;}
"long"  {return KW_LONG;}
"float" {return KW_FLOAT;}
"double" {return KW_DOUBLE;}
"if"    { return KW_IF; }
"then"  {return KW_THEN;}
"else"  {return KW_ELSE;}
"while" {return KW_WHILE;}
"for"   {return KW_FOR;}
"read"  {return KW_READ;}
"print" {return KW_PRINT;}
"return" {return KW_RETURN;}
"<=" {return OPERATOR_LE;}
">=" {return OPERATOR_GE;}
"==" {return OPERATOR_EQ;}
"!=" {return OPERATOR_NE;}
"&&" {return OPERATOR_AND;}
"||" {return OPERATOR_OR;}
[-,;:()\[\]{}+*/<>=!&$#] {return yytext[0];}
[0-9]+		{yylval.symbol = hashInsert(SYMBOL_LIT_INT, yytext); return LIT_INTEGER;}
[0-9]+\.[0-9]+	{yylval.symbol = hashInsert(SYMBOL_LIT_REAL, yytext);  return LIT_REAL;}
\'.\'		{yylval.symbol = hashInsert(SYMBOL_LIT_CHAR, yytext);  return LIT_CHAR;}
\"(\\.|[^"])*\" {yylval.symbol = hashInsert(SYMBOL_LIT_STRING, yytext); return LIT_STRING;}
[a-zA-Z_]([a-zA-Z_0-9 ]*[a-zA-Z_0-9])* {yylval.symbol = hashInsert(SYMBOL_IDENTIFIER, yytext); return TK_IDENTIFIER;}
[ \t] 
[\n]    {lineNumber++;}
"//".*
"/*"    {BEGIN(COMMENT);}
. 	{return TOKEN_ERROR;}

<COMMENT>"*/" {BEGIN(INITIAL);}
<COMMENT>"\n" {lineNumber++;}
<COMMENT>.   

%%

int yywrap(){ 
    running = 0;  
    return 1; 
}

FILE* file(char* filename){
    yyin = fopen(filename,"r");
    return yyin;
}

int isRunning(){
    return running;
}

int ascii(){
    return yytext[0];
}

int getLineNumber(void){
    return lineNumber;
}

void initMe(){
	hashInit();
} 
