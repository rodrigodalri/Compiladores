/* 
	ETAPA 6 - TRABALHO DE COMPILADORES
	Gabriel Zillmer e Rodrigo dal Ri 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "astree.h"

ASTREE* astreeCreate(int type, Hash_Node* symbol, ASTREE* son0, ASTREE* son1, ASTREE* son2, ASTREE* son3){
	ASTREE *node = calloc(1, sizeof(ASTREE));
	node->type = type;
	if (symbol != NULL)
		node->symbol = symbol;

	node->son[0] = son0;
	node->son[1] = son1;
	node->son[2] = son2;
	node->son[3] = son3; 

	return node;
}

void astreePrint(int level, ASTREE *node){
	if(!node) return;
	int i;
	for(i = 0; i < level; i++) fprintf(stderr,"  ");
	fprintf(stderr, "ASTREE(");
	switch(node->type){
		case ASTREE_SYMBOL: fprintf(stderr, "ASTREE_SYMBOL"); break;
		case ASTREE_ADD: fprintf(stderr, "ASTREE_ADD"); break;
		case ASTREE_SUB: fprintf(stderr, "ASTREE_SUB"); break;
		case ASTREE_MUL: fprintf(stderr, "ASTREE_MUL"); break;
		case ASTREE_DIV: fprintf(stderr, "ASTREE_DIV"); break;
		case ASTREE_L: fprintf(stderr, "ASTREE_L"); break;
		case ASTREE_G: fprintf(stderr, "ASTREE_G"); break;
		case ASTREE_LE: fprintf(stderr, "ASTREE_LE"); break;
		case ASTREE_GE: fprintf(stderr, "ASTREE_GE"); break;		
		case ASTREE_EQ: fprintf(stderr, "ASTREE_EQ"); break;
		case ASTREE_NE: fprintf(stderr, "ASTREE_NE"); break;
		case ASTREE_AND: fprintf(stderr, "ASTREE_AND"); break;
		case ASTREE_OR: fprintf(stderr, "ASTREE_OR"); break;		
		case ASTREE_ATR: fprintf(stderr, "ASTREE_ATR"); break;
		case ASTREE_PARAM: fprintf(stderr, "ASTREE_PARAM"); break;
		case ASTREE_FUNDEF: fprintf(stderr, "ASTREE_FUNDEF"); break;
		case ASTREE_FUNCALL: fprintf(stderr, "ASTREE_FUNCALL"); break;
		case ASTREE_CMDL: fprintf(stderr, "ASTREE_CMDL"); break;
		case ASTREE_DFNL: fprintf(stderr, "ASTREE_DFNL"); break;		
		case ASTREE_PARL: fprintf(stderr, "ASTREE_PARL"); break;
		case ASTREE_INTL: fprintf(stderr, "ASTREE_INTL"); break;
		case ASTREE_BYTE: fprintf(stderr, "ASTREE_BYTE"); break;
		case ASTREE_SHORT: fprintf(stderr, "ASTREE_SHORT"); break;
		case ASTREE_LONG: fprintf(stderr, "ASTREE_LONG"); break;		
		case ASTREE_FLOAT: fprintf(stderr, "ASTREE_FLOAT"); break;
		case ASTREE_DOUBLE: fprintf(stderr, "ASTREE_DOUBLE"); break;
		case ASTREE_PRINT: fprintf(stderr, "ASTREE_PRINT"); break;
		case ASTREE_PRINTL: fprintf(stderr, "ASTREE_PRINTL"); break;
		case ASTREE_READ: fprintf(stderr, "ASTREE_READ"); break;	
		case ASTREE_RETURN: fprintf(stderr, "ASTREE_RETURN"); break;
		case ASTREE_IF: fprintf(stderr, "ASTREE_IF"); break;
		case ASTREE_WHILE: fprintf(stderr, "ASTREE_WHILE"); break;
		case ASTREE_PARENTHESIS: fprintf(stderr, "ASTREE_PARENTHESIS"); break;
		case ASTREE_BRACES: fprintf(stderr, "ASTREE_BRACES"); break;
		case ASTREE_ARRAY_WRITE: fprintf(stderr, "ASTREE_WRITE"); break;
		case ASTREE_ARRAY_READ: fprintf(stderr, "ASTREE_ARRAY_READ"); break;		
		case ASTREE_VARINI: fprintf(stderr, "ASTREE_VARINI"); break;
		case ASTREE_ARRINI: fprintf(stderr, "ASTREE_ARRINI"); break;
		case ASTREE_NOT: fprintf(stderr, "ASTREE_NOT"); break;
		case ASTREE_ELSE: fprintf(stderr, "ASTREE_ELSE"); break;
		default: fprintf(stderr, "Node Type: %d", node->type); break;
	}
	if(node->symbol){
			fprintf(stderr, ", %s)\n", node->symbol->text);
	}
	else{
			fprintf(stderr, ",)\n");
	}
	for(i = 0; i < MAX_SONS; i++){
		astreePrint(level+1, node->son[i]);
	}
}

void asmAddData(ASTREE *node)
{
	
	if(!node) return;
	if(node->type == ASTREE_VARINI){
    		asmAddVariable(node);
	}
	else if(node->type == ASTREE_ARRINI){
        	asmAddArray(node);
	}
    	else if(node->type == ASTREE_SYMBOL){      		
		asmAddPrint(node);
    	}
    	else if(node->type == ASTREE_PARAM){
        	asmAddParam(node);
    	}
    
	int i;
	for(i = 0; i < MAX_SONS; i++){
		asmAddData(node->son[i]);
	}
}


void asmAddVariable(ASTREE* var)
{
	FILE *fout = fopen("asm.s", "a");
	
	if(!var) return;
	if(var->type == ASTREE_VARINI)
	{	
		fprintf(fout, "\t.globl	_%s\n"
			"\t.data\n"
			"\t.type	_%s, @object\n"
			"\t.size	_%s, 4\n"
			"_%s:\n", var->symbol->text, var->symbol->text, var->symbol->text, var->symbol->text);
		
		if(var->son[0]->type == ASTREE_FLOAT || var->son[0]->type == ASTREE_DOUBLE){
			fprintf(fout, "\t.float	%s\n", var->son[1]->symbol->text);
		}
		else{
			fprintf(fout, "\t.long	%s\n", var->son[1]->symbol->text);
		}
	}
	fclose(fout);
}

void asmAddParam(ASTREE* var)
{
	FILE *fout = fopen("asm.s", "a");

	if(var->type == ASTREE_PARAM)
	{		
		fprintf(fout, "\t.globl	_%s\n"
			"\t.data\n"
			"\t.type	_%s, @object\n"
			"\t.size	_%s, 4\n"
			"_%s:\n"
			"\t.long	0\n", var->symbol->text, var->symbol->text, var->symbol->text, var->symbol->text);
	}

	fclose(fout);
}

void asmAddArray(ASTREE* arr)
{
	FILE *fout = fopen("asm.s", "a");

	if(arr->type == ASTREE_ARRINI)
	{
		fprintf(fout, "\t.globl	_%s\n"
			"\t.data\n"
			"\t.type	_%s, @object\n"
			"\t.size	_%s, %d\n"
			"_%s:\n", arr->symbol->text, arr->symbol->text, arr->symbol->text, 4*atoi(arr->son[1]->symbol->text), arr->symbol->text);
			ASTREE* aux;
	for(aux = arr->son[1]->son[0]; aux; aux = aux->son[0])
	{
		fprintf(fout, "\t.long	%s\n", aux->symbol->text);
	}
	}

	fclose(fout);
}

int numLC = 2;

void asmAddPrint(ASTREE* arr)
{
	FILE *fout = fopen("asm.s", "a");
   
     	char* lable = (char*) calloc(1, sizeof(char));
	
	if(arr->type == ASTREE_SYMBOL && arr->symbol->type == 103)
	{
       
	        if(arr->symbol)
		{
	        strcpy(lable, ".LC");
	        fprintf(fout, "\t.section\t .rodata\n%s%d:\n\t.string %s \n", lable, numLC ,arr->symbol->text);
            	numLC +=1;          
        	}
        	
	}
}
