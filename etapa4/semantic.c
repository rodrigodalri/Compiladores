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
	//setFunParam(n);
	CheckUndeclared();
	CheckUsage(n);
	CheckOperands(n);
	checkFunCall(n);
}

//verifica tipo do retorno
void checkReturnFun(ASTREE* node, ASTREE* nodefunc)
{	int i = 0;

	if(!node) return;

	for(i = 0; i < MAX_SONS; i++) checkReturnFun(node->son[i], nodefunc);
	
	if(node->type == ASTREE_RETURN){
		if(node->son[0] != NULL){ 
			semanticSetRemnant(node->son[0]); 
			if(node->son[0]->symbol->datatype < SYMBOL_DATATYPE_BYTE || node->son[0]->symbol->datatype > SYMBOL_DATATYPE_DOUBLE){
				fprintf(stderr, "ERRO Semantico. Retorno invalido na funcao '%s'.\n", nodefunc->symbol->text);	
				exit(4);
			}
		}
	}

}

//seta numeoro e tipo de parametros da funcao
void setFunParam(ASTREE* node)
{
	int i = 0;

	if(!node) return;
	
	for(i = 0; i < MAX_SONS; i++) setFunParam(node->son[i]);
	
	if(node->type == ASTREE_FUNDEF){
		if(node->symbol){
			
			int numParam = 0;
			
			ASTREE* q = node->son[1];
			
			do{
				if(q->son[0] != NULL) 
					numParam++;
					
				q = q->son[1];    
			}while(q != NULL);
					
				node->symbol->numparam = numParam;			
			
			
			if(numParam > 0){
				ASTREE* p = node->son[1];
				do{
					if(p->son[0] != NULL){ 

						p->son[0]->symbol->type = SYMBOL_VAR;

						if(p->son[0]->son[0]->type == ASTREE_BYTE)   p->son[0]->symbol->datatype = SYMBOL_DATATYPE_BYTE;
						if(p->son[0]->son[0]->type == ASTREE_SHORT)  p->son[0]->symbol->datatype = SYMBOL_DATATYPE_SHORT;
						if(p->son[0]->son[0]->type == ASTREE_LONG)   p->son[0]->symbol->datatype = SYMBOL_DATATYPE_LONG;
						if(p->son[0]->son[0]->type == ASTREE_FLOAT)  p->son[0]->symbol->datatype = SYMBOL_DATATYPE_FLOAT;
						if(p->son[0]->son[0]->type == ASTREE_DOUBLE) p->son[0]->symbol->datatype = SYMBOL_DATATYPE_DOUBLE;

						i++;
					}
					p = p->son[1];   
				}while(p != NULL);
			}

			// checa corpo da funcao (cmd - node->son[2])
			checkReturnFun(node->son[2],node);
		}
	}
}

//verificar numero e tipo de parametros declarados e usados 
void checkFunCall(ASTREE* node)
{
	int i = 0;

	if(!node) return;
	
	for(i = 0; i < MAX_SONS; i++) checkFunCall(node->son[i]);

	if(node->type == ASTREE_FUNCALL){
		if(node->symbol){
			int numParamCall = 0;
			ASTREE* p = node->son[0]; 
			do{	
				if(p->son[0] != NULL) 
					numParamCall++;
				p = p->son[1];   
			}while(p != NULL);
						fprintf(stderr, "\n %d \n", numParamCall);//testes
						fprintf(stderr, "\n %d \n", node->symbol->numparam);
			if(numParamCall < node->symbol->numparam){
				fprintf(stderr, "ERRO Semantico: o numero de parametros da chamada eh menor que o da funcao '%s'.\n", node->symbol->text); exit(4);
			}else if(numParamCall > node->symbol->numparam){
				fprintf(stderr, "ERRO Semantico: o numero de parametros da chamada eh maior que o da funcao '%s'.\n", node->symbol->text); exit(4);
			}
	
		//ainda nao passou daqui
			if(numParamCall > 0){
				ASTREE* p = node->son[0]; 
				do{
					if(p->son[0] != NULL){
						semanticSetRemnant(p->son[0]); 
						if(p->son[0]->symbol->datatype < SYMBOL_DATATYPE_BYTE || p->son[0]->symbol->datatype > SYMBOL_DATATYPE_DOUBLE){
							fprintf(stderr, "Erro semantico: parametro invalido na chamada da funcao '%s'.\n", node->symbol->text);	
							exit(4);
						}
					}
					p = p->son[1];    
				}while(p != NULL);
			}
		}
	}

}

int greaterDatatype(int a, int b){
	
	if(a > b) 
		return a;
	else 
		return b;
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








void semanticSetRemnant(ASTREE* node){
	int i = 0;

	if(!node) return;
	
	for(i = 0; i < MAX_SONS; i++) semanticSetRemnant(node->son[i]);
	
	if(node->type == ASTREE_FUNCALL ||
		node->type == ASTREE_SYMBOL ||
		node->type == ASTREE_ARRAY_READ){
		//node->symbol->datatype = symbolToNodeDatatype(node->symbol->datatype); 					
	}

	if(node->type == ASTREE_ADD ||
		node->type == ASTREE_SUB || 
		node->type == ASTREE_MUL || 
		node->type == ASTREE_DIV ){
		node->symbol->datatype = greaterDatatype(node->son[0]->symbol->datatype, node->son[1]->symbol->datatype); 					
	}

	if(node->type == ASTREE_PARENTHESIS){
		node->symbol->datatype = node->son[0]->symbol->datatype; 					
	}

}


