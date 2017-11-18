/* 
	ETAPA 4 - TRABALHO DE COMPILADORES
	Gabriel Zillmer e Rodrigo dal Ri 
*/

#include "hash.h"

#ifndef ASTREE_H
#define ASTREE_H

#define MAX_SONS 4

#define ASTREE_SYMBOL 0

#define ASTREE_ADD 1
#define ASTREE_SUB 2
#define ASTREE_MUL 3
#define ASTREE_DIV 4

#define ASTREE_L 5
#define ASTREE_G 6
#define ASTREE_LE 7
#define ASTREE_GE 8
#define ASTREE_EQ 9 
#define ASTREE_NE 10
#define ASTREE_AND 11
#define ASTREE_OR 12

#define ASTREE_PARAM 13
#define ASTREE_FUNDEF 14
#define ASTREE_FUNCALL 15

#define ASTREE_BYTE 16
#define ASTREE_SHORT 17
#define ASTREE_LONG 18
#define ASTREE_FLOAT 19
#define ASTREE_DOUBLE 20

#define ASTREE_PARENTHESIS 21
#define ASTREE_BRACES 22

#define ASTREE_ATR 23
#define ASTREE_ARRAY_WRITE 24
#define ASTREE_ARRAY_READ 25

#define ASTREE_VARDECL 26
#define ASTREE_ARRDECL 27
#define ASTREE_VARINI 28
#define ASTREE_ARRINI 29

#define ASTREE_PRINT 30
#define ASTREE_PRINTL 31
#define ASTREE_READ 32
#define ASTREE_RETURN 33
#define ASTREE_WHILE 34
#define ASTREE_IF 35
#define ASTREE_ELSE 36
#define ASTREE_NOT 37

#define ASTREE_CMDL 100
#define ASTREE_DFNL 101
#define ASTREE_PARL 102
#define ASTREE_PARCALLL 103
#define ASTREE_INTL 104

#define ASTREE_QUOTES 105

typedef struct astree{
	int type;
	Hash_Node *symbol;
	struct astree* son[MAX_SONS];
}ASTREE;

ASTREE* astreeCreate(int type, Hash_Node* symbol, ASTREE* son0, ASTREE* son1, ASTREE* son2, ASTREE* son3);

void astreePrint(int level, ASTREE *node);


#endif
