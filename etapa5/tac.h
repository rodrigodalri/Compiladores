/* 
	ETAPA 5 - TRABALHO DE COMPILADORES
	Gabriel Zillmer e Rodrigo dal Ri 
*/
#include "hash.h"
#include "astree.h"

#ifndef TAC_H
#define TAC_H

#define TAC_SYMBOL 1
#define TAC_ADD 2
#define TAC_SUB 3
#define TAC_MUL 4
#define TAC_DIV 5
#define TAC_L 6
#define TAC_G 7
#define TAC_LE 8
#define TAC_GE 9
#define TAC_EQ 10 
#define TAC_NE 11
#define TAC_AND 12
#define TAC_OR 13
#define TAC_NOT 14
#define TAC_MOVE 15
#define TAC_READ 16
#define TAC_RET 17
#define TAC_INC 18
#define TAC_PRINT 19
#define TAC_PARPUSH 20
#define TAC_FUNCALL 21
#define TAC_IFZ 22
#define TAC_LABEL 23
#define TAC_JUMP 24
#define TAC_BEGINFUN 25
#define TAC_ENDFUN 26
#define TAC_AREAD 27
#define TAC_AWRITE 28
#define TAC_AINIPUSH 29
#define TAC_ASIZE 30
#define TAC_ADECLPOP 31
#define TAC_PARPOP 32
			
typedef struct tac_struct{
	int type;
	Hash_Node *res;
	Hash_Node *op1;
	Hash_Node *op2;
	struct tac_struct *prev;
	struct tac_struct *next; 
} TAC;

TAC* tacCreate(int type, Hash_Node *res, Hash_Node *op1, Hash_Node *op2);

TAC* tacJoin(TAC* l1, TAC* l2);
void tacPrintBack(TAC *last);
TAC* tacGenerate(ASTREE *node);
TAC* tacReverse(TAC* tac);
void tacPrintFoward(TAC* first);
void tacPrintOne(TAC* tac);
TAC* makeIfThenElse(TAC* code0, TAC* code1, TAC* code2);
TAC* makeWhile(TAC* code0, TAC* code1);
TAC* makeFor(TAC* symbol, TAC* code0, TAC* code1, TAC* code2);
TAC* makeFunction(TAC* symbol, TAC* par, TAC* code);

#endif
