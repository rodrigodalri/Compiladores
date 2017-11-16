/* 
	ETAPA 4 - TRABALHO DE COMPILADORES
	Gabriel Zillmer e Rodrigo dal Ri
*/

#include <stdio.h>
#include <stdlib.h>

#include "semantic.h"
#include "hash.h"
#include "y.tab.h"

ASTREE* n;

void checkSemantic(ASTREE* node)
{
	n = node;

	SetTypes(n); 
	CheckUndeclared();
	CheckUsage(n);
	CheckOperands(n);
}


void CheckUndeclared(void)
{
	hashCheckUndeclared();
}

void SetTypes(ASTREE* node)
{
	int i;
	if (!node) return;
	
	if(node->type == ASTREE_VARINI){
		if(node->symbol->type != SYMBOL_IDENTIFIER){
			fprintf(stderr,"ERRO: Identificador %s, ja foi declarado! \n",node->symbol->text);
			exit(4); 
		}
		else{
			node->symbol->type = SYMBOL_VAR;
			if(node->son[0]->type == ASTREE_BYTE) node->symbol->datatype = SYMBOL_DATATYPE_BYTE;
			if(node->son[0]->type == ASTREE_SHORT) node->symbol->datatype = SYMBOL_DATATYPE_SHORT;
			if(node->son[0]->type == ASTREE_LONG) node->symbol->datatype = SYMBOL_DATATYPE_LONG;
			if(node->son[0]->type == ASTREE_FLOAT) node->symbol->datatype = SYMBOL_DATATYPE_FLOAT;
			if(node->son[0]->type == ASTREE_DOUBLE) node->symbol->datatype = SYMBOL_DATATYPE_DOUBLE;
		}
	}
	if(node->type == ASTREE_ARRINI){
		if(node->symbol->type != SYMBOL_IDENTIFIER){
			fprintf(stderr,"ERRO: Identificador %s, ja foi declarado! \n",node->symbol->text);
			exit(4);
		}
		else{
			node->symbol->type = SYMBOL_ARR;
			if(node->son[0]->type == ASTREE_BYTE) node->symbol->datatype = SYMBOL_DATATYPE_BYTE;
			if(node->son[0]->type == ASTREE_SHORT) node->symbol->datatype = SYMBOL_DATATYPE_SHORT;
			if(node->son[0]->type == ASTREE_LONG) node->symbol->datatype = SYMBOL_DATATYPE_LONG;
			if(node->son[0]->type == ASTREE_FLOAT) node->symbol->datatype = SYMBOL_DATATYPE_FLOAT;
			if(node->son[0]->type == ASTREE_DOUBLE) node->symbol->datatype = SYMBOL_DATATYPE_DOUBLE;
		}
	}
	if (node->type == ASTREE_FUNDEF){
		if(node->symbol->type != SYMBOL_IDENTIFIER){
			fprintf(stderr, "ERRO: Identificador %s, ja foi declarado! \n", node->symbol->text);
			exit(4);
		}
		else{
			node->symbol->type = SYMBOL_FUN;
			if(node->son[0]->type == ASTREE_BYTE) node->symbol->datatype = SYMBOL_DATATYPE_BYTE;
			if(node->son[0]->type == ASTREE_SHORT) node->symbol->datatype = SYMBOL_DATATYPE_SHORT;
			if(node->son[0]->type == ASTREE_LONG) node->symbol->datatype = SYMBOL_DATATYPE_LONG;
			if(node->son[0]->type == ASTREE_FLOAT) node->symbol->datatype = SYMBOL_DATATYPE_FLOAT;
			if(node->son[0]->type == ASTREE_DOUBLE) node->symbol->datatype = SYMBOL_DATATYPE_DOUBLE;
		}
	}
	if(node->type == ASTREE_PARAM){
		if(node->symbol->type != SYMBOL_IDENTIFIER){
			fprintf(stderr, "ERRO: Identificador %s, ja foi declarado! \n", node->symbol->text);
			exit(4);
		}
		else{
			node->symbol->type = SYMBOL_VAR;
			if(node->son[0]->type == ASTREE_BYTE) node->symbol->datatype = SYMBOL_DATATYPE_BYTE;
			if(node->son[0]->type == ASTREE_SHORT) node->symbol->datatype = SYMBOL_DATATYPE_SHORT;
			if(node->son[0]->type == ASTREE_LONG) node->symbol->datatype = SYMBOL_DATATYPE_LONG;
			if(node->son[0]->type == ASTREE_FLOAT) node->symbol->datatype = SYMBOL_DATATYPE_FLOAT;
			if(node->son[0]->type == ASTREE_DOUBLE) node->symbol->datatype = SYMBOL_DATATYPE_DOUBLE;
		}
	}
	for (i=0; i<MAX_SONS; ++i)
		SetTypes(node->son[i]);
}

void CheckUsage(ASTREE *node)
{
	int i;
	if(!node) return;
	
	switch(node->type){
		case ASTREE_ATR: if(node->symbol->type != SYMBOL_VAR)
			{
				fprintf(stderr, "Semantic ERROR: identifier %s must be scalar.\n", node->symbol->text);
				exit(4);
			}
			break;
		case ASTREE_ARRAY_WRITE: if(node->symbol->type != SYMBOL_ARR)
			{
				fprintf(stderr, "Semantic ERROR: identifier %s must be vector.\n", node->symbol->text);
				exit(4);
			}
			break;
		case ASTREE_FUNCALL: if(node->symbol->type != SYMBOL_FUN)
			{
				fprintf(stderr, "Semantic ERROR: identifier %s must be a function.\n", node->symbol->text);
				exit(4);
			}
			break;
		case ASTREE_ARRAY_READ: if(node->symbol->type != SYMBOL_ARR)
			{
				fprintf(stderr, "Semantic ERROR: identifier %s must be a vector.\n", node->symbol->text);
				exit(4);
			}
			break; 
		case ASTREE_SYMBOL: if(node->symbol->type != SYMBOL_VAR && node->symbol->type != SYMBOL_LIT_INT && node->symbol->type != SYMBOL_LIT_REAL && node->symbol->type != SYMBOL_LIT_CHAR && node->symbol->type != SYMBOL_LIT_STRING)
			{
				fprintf(stderr, "Semantic ERROR: identifier %s must be scalar.\n", node->symbol->text);
				exit(4);
			}
			break;
		default: break;
	}
	
	for(i=0; i <MAX_SONS; ++i)
		CheckUsage(node->son[i]);
}

void CheckOperands(ASTREE* node)
{
	int i;
	if (!node) return;
	
	if (node->type == ASTREE_ADD || node->type == ASTREE_SUB || node->type == ASTREE_MUL || node->type == ASTREE_DIV || node->type == ASTREE_G || node->type == ASTREE_L || node->type == ASTREE_NE || node->type == ASTREE_EQ || node->type == ASTREE_LE || node->type == ASTREE_GE){
		if(node->son[0]->type == ASTREE_G ||
		   node->son[0]->type == ASTREE_L || 
		   node->son[0]->type == ASTREE_GE || 
		   node->son[0]->type == ASTREE_LE || 
		   node->son[0]->type == ASTREE_NE || 
		   node->son[0]->type == ASTREE_EQ || 
		   node->son[0]->type == ASTREE_OR || 
		   node->son[0]->type == ASTREE_AND|| 
                   node->son[0]->type == ASTREE_NOT){

			fprintf(stderr, "ERRO: Operando esquerdo não pode ser logico. \n");
			exit(4);
		}
		if(node->son[1]->type == ASTREE_G ||
		   node->son[1]->type == ASTREE_L || 
		   node->son[1]->type == ASTREE_GE || 
		   node->son[1]->type == ASTREE_LE || 
		   node->son[1]->type == ASTREE_NE || 
		   node->son[1]->type == ASTREE_EQ || 
		   node->son[1]->type == ASTREE_OR || 
		   node->son[1]->type == ASTREE_AND|| 
                   node->son[1]->type == ASTREE_NOT){

			fprintf(stderr, "ERRO: Operando direito não pode ser logico. \n");
			exit(4);
		}
	}
		
	if (node->type == ASTREE_AND || node->type == ASTREE_OR || node->type == ASTREE_NOT){
	
		if(node->son[0]->type == ASTREE_MUL ||
		   node->son[0]->type == ASTREE_ADD || 
		   node->son[0]->type == ASTREE_SUB || 
		   node->son[0]->type == ASTREE_DIV){

			fprintf(stderr, "ERRO: Operando esquerdo não pode ser aritmético. \n");
			exit(4);
		}
		if(node->son[1]->type == ASTREE_MUL ||
		   node->son[1]->type == ASTREE_ADD || 
		   node->son[1]->type == ASTREE_SUB || 
		   node->son[1]->type == ASTREE_DIV){

			fprintf(stderr, "ERRO: Operando direito não pode ser aritmético. \n");
			exit(4);
		}
	}
	
	for (i=0; i<MAX_SONS; ++i)
		CheckOperands(node->son[i]);
}


