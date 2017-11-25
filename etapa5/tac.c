/* 
	ETAPA 5 - TRABALHO DE COMPILADORES
	Gabriel Zillmer e Rodrigo dal Ri 
*/
#include <stdio.h>
#include <stdlib.h>
#include "tac.h"

TAC* tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2){
	TAC *n = (TAC*) calloc(1, sizeof(TAC));
	n->type = type;
	n->res = res;
	n->op1 = op1;
	n->op2 = op2;
	n->prev = 0;
	n->next = 0;	
	return n;
}



