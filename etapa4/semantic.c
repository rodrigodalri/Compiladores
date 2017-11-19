/* 
	ETAPA 4 - TRABALHO DE COMPILADORES
	Gabriel Zillmer e Rodrigo dal Ri
*/

#include <stdio.h>
#include <stdlib.h>

#include "semantic.h"
#include "hash.h"
#include "y.tab.h"

int semanticError = 0;

int checkSemantic(ASTREE* node)
{

	setTypes(node); 
	checkUndeclared();
	linkStart(node, node);
	checkUsage(node);
	checkOperands(node);

	return semanticError;
	
}

void checkUndeclared(void)
{
	hashCheckUndeclared();
}

void checkOperands(ASTREE* node)
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
			semanticError++;
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
			semanticError++;
		}
	}
		
	if (node->type == ASTREE_AND || node->type == ASTREE_OR || node->type == ASTREE_NOT){
	
		if(node->son[0]->type == ASTREE_MUL ||
		   node->son[0]->type == ASTREE_ADD || 
		   node->son[0]->type == ASTREE_SUB || 
		   node->son[0]->type == ASTREE_DIV){

			fprintf(stderr, "ERRO: Operando esquerdo não pode ser aritmético. \n");
			semanticError++;
		}
		if(node->son[1]->type == ASTREE_MUL ||
		   node->son[1]->type == ASTREE_ADD || 
		   node->son[1]->type == ASTREE_SUB || 
		   node->son[1]->type == ASTREE_DIV){

			fprintf(stderr, "ERRO: Operando direito não pode ser aritmético. \n");
			semanticError++;
		}
	}
	
	for (i=0; i<MAX_SONS; ++i)
		checkOperands(node->son[i]);
}

void setTypes(ASTREE* node)
{
	int i;
	if (!node) return;
	
	if(node->type == ASTREE_VARINI){
		if(node->symbol->type != SYMBOL_IDENTIFIER){
			fprintf(stderr,"ERRO: Identificador %s, ja foi declarado! \n",node->symbol->text);
			semanticError++;
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
			semanticError++;
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
			semanticError++;
		}
		else{
			node->symbol->type = SYMBOL_FUN;
			node->symbol->numparam = countNumParam(node->son[1]);
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
			semanticError++;
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
		setTypes(node->son[i]);
}

void checkUsage(ASTREE *node)
{
	int i;
	
	if(!node) return;
	
	switch(node->type){
		case ASTREE_ATR: if(node->symbol->type != SYMBOL_VAR)
			{
				fprintf(stderr, "ERRO: identificador %s deve ser escalar.\n", node->symbol->text);
				semanticError++;
			}
			break;
		case ASTREE_FUNCALL: if(node->symbol->type != SYMBOL_FUN)
			{
				fprintf(stderr, "ERRO: identificador %s deve ser funcao.\n", node->symbol->text);
				semanticError++;
			}
			checkNumParam(node);
			checkTypeParam(node, node->start); 
			break;
		case ASTREE_FUNDEF: checkReturn(node, node->son[2]);
			break;
		case ASTREE_ARRAY_WRITE: if(node->symbol->type != SYMBOL_ARR)
			{
				fprintf(stderr, "ERRO: identificador %s deve ser vetor.\n", node->symbol->text);
				semanticError++;
			}
			if(node->son[0]->symbol != NULL) {	
			if(node->son[0]->symbol->datatype == SYMBOL_DATATYPE_FLOAT || node->son[0]->symbol->datatype == SYMBOL_DATATYPE_DOUBLE)
			{
				fprintf(stderr, "ERRO: indice deve ser int.\n");
				semanticError++;
			}}
			break;
		case ASTREE_ARRAY_READ: if(node->symbol->type != SYMBOL_ARR)
			{
				fprintf(stderr, "ERRO: identificador %s deve ser vetor.\n", node->symbol->text);
				semanticError++;
			}
			if(node->son[0]->symbol != NULL) {			
			if(node->son[0]->symbol->datatype == SYMBOL_DATATYPE_FLOAT || node->son[0]->symbol->datatype == SYMBOL_DATATYPE_DOUBLE)
			{
				fprintf(stderr, "ERRO: indice deve ser int.\n");
				semanticError++;
			}}
			break;
		case ASTREE_IF:  
   			{	if(node->son[0]->symbol != NULL) {
        			if (node->son[0]->type != ASTREE_L && node->son[0]->type != ASTREE_G && node->son[0]->type != ASTREE_LE && node->son[0]->type != ASTREE_GE && node->son[0]->type != ASTREE_EQ && node->son[0]->type != ASTREE_NE && node->son[0]->type != ASTREE_NOT)
       				{
            				fprintf(stderr, "ERRO: deve ser condicional\n");
            				semanticError++;
        			}}
    			}
			break; 
		case ASTREE_WHILE:
   			{	if(node->son[0]->symbol != NULL) {
        			if (node->son[0]->type != ASTREE_L && node->son[0]->type != ASTREE_G && node->son[0]->type != ASTREE_LE && node->son[0]->type != ASTREE_GE && node->son[0]->type != ASTREE_EQ && node->son[0]->type != ASTREE_NE && node->son[0]->type != ASTREE_NOT)
       				{
            				fprintf(stderr, "ERRO: deve ser condicional\n");
            				semanticError++;
        			}}
    			} 
			break;
		case ASTREE_PRINT:
			if(node->son[0]->symbol != NULL) {
			if(node->son[0]->symbol->type != SYMBOL_LIT_STRING)
			{
				fprintf(stderr, "ERRO: deve ser string.\n");
				semanticError++;
			}}
			break;
		case ASTREE_READ:if(node->symbol->type != SYMBOL_VAR)
			{
				fprintf(stderr, "ERRO: identificador %s deve ser escalar.\n", node->symbol->text);
				semanticError++;
			}
		break;
		case ASTREE_SYMBOL: if(node->symbol->type != SYMBOL_VAR && node->symbol->type != SYMBOL_LIT_INT && node->symbol->type != SYMBOL_LIT_REAL && node->symbol->type != SYMBOL_LIT_CHAR && node->symbol->type != SYMBOL_LIT_STRING)
			{
				fprintf(stderr, "ERRO: identificador %s deve ser escalar.\n", node->symbol->text);
				semanticError++;
			}
			break;
		default: break;
	}
	
	for(i=0; i <MAX_SONS; ++i)
		checkUsage(node->son[i]);
}

void checkReturn(ASTREE *nodefunc, ASTREE *node)
{	
	int i = 0;
	int data;
	
	if(!node) return;
	
	for(i = 0; i < MAX_SONS; i++) 
		checkReturn(nodefunc, node->son[i]);
	
	if(node->type == ASTREE_RETURN){ 
		if(node->son[0] != NULL) 
			
			if(node->son[0]->type == ASTREE_PARENTHESIS)
			{	
				if(node->son[0]->son[0]->type == ASTREE_ADD || node->son[0]->son[0]->type == ASTREE_SUB || node->son[0]->son[0]->type == ASTREE_MUL || node->son[0]->son[0]->type == ASTREE_DIV ){
			
				data = greaterDatatype(node->son[0]->son[0]->son[0]->symbol->datatype, node->son[0]->son[0]->son[1]->symbol->datatype);
				}
				else 
				{
					data = node->son[0]->son[0]->symbol->datatype; 
				}			
			}

			if(nodefunc->symbol != NULL)
			{
				if (data != nodefunc->symbol->datatype)
				{
					fprintf(stderr, "ERRO: tipo retorno invalido.\n");	
					semanticError++;
				}
			}
	}
}

int greaterDatatype(int a, int b)
{
	if(a > b) return a;
	else return b;
}


void checkTypeParam(ASTREE* nodecall, ASTREE* nodedef) 
{
	if(!nodecall || !nodedef) return;
	
	if(nodecall->son[0] != NULL && nodedef->son[1] != NULL)
	{
		nodecall = nodecall->son[0];	
		nodedef = nodedef->son[1];	
	
		while(nodecall != NULL && nodedef != NULL)
		{	
			if(nodecall->son[0]->symbol != NULL && nodedef->son[0]->symbol != NULL) 
				{
					if(nodecall->son[0]->symbol->datatype > nodedef->son[0]->symbol->datatype)
					{
						fprintf(stderr, "ERRO: Tipo de parametro incorreto\n");
						semanticError++;
					}
				}
				nodecall = nodecall->son[1];
				nodedef = nodedef->son[1];			
		}
	}
}

void checkNumParam(ASTREE* node)
{
	int numParam = 0;
	int correct = node->symbol->numparam;
	
	numParam = countNumParam(node->son[0]);

	if(numParam != correct)
	{
		fprintf(stderr, "ERRO: Numero de parametros incorretos\n");
		semanticError++;
	}	
}

int countNumParam(ASTREE *node)
{
	if(!node) return 0;
	else{
		return 1 + countNumParam(node->son[1]);
	}

	return 0;
}

