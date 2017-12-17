/* 
	ETAPA 6 - TRABALHO DE COMPILADORES
	Gabriel Zillmer e Rodrigo dal Ri 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hash.h"

void hashInit()
{
	int i;
	for(i=0;i<=HASH_SIZE;i++)
		Table[i] = NULL;
}

void hashPrint(void)
{
  int i;
  Hash_Node *node;
  
printf("HASH TABLE\n");
for(i=0; i<HASH_SIZE; ++i)
    for(node=Table[i]; node; node = node->next){
     
	printf("id: %d	", i);
	printf("Type: %d	", Table[i]->type);
	printf("DataType: %d	", Table[i]->datatype);
	//printf("NumParam: %d	", Table[i]->numparam);
	printf("Text: %s\n", Table[i]->text);
	}
printf("HASH TABLE\n");
}

int hashAddress(char* text)
{
	int i;
	int address = 1;
	for(i=0;i<strlen(text);i++)
		address = (address * text[i])%HASH_SIZE + 1;
	return address - 1;
}

Hash_Node* hashFind(char* text)
{
	int address = hashAddress(text);
	Hash_Node* chainedNode = Table[address];

	while(chainedNode != NULL)
	{
		int a = strcmp(text, chainedNode->text);
		if(a == 0)
			return chainedNode;
		else
			chainedNode = chainedNode->next;	
	}
	
	return 0;
}

Hash_Node *hashInsert(int type, char *text)
{
	Hash_Node *newnode;
	int address;
	
	if((newnode = hashFind(text)) != NULL)
		return newnode; 
	
	address = hashAddress(text);
	newnode = (Hash_Node*) calloc(1, sizeof(Hash_Node));
	newnode->type = type;
	if (type == SYMBOL_LIT_INT) newnode->datatype = SYMBOL_DATATYPE_LONG;
	if (type == SYMBOL_LIT_REAL) newnode->datatype = SYMBOL_DATATYPE_DOUBLE;
	if (type == SYMBOL_LIT_CHAR) newnode->datatype = SYMBOL_DATATYPE_LONG;
	if (type == SYMBOL_LIT_STRING) newnode->datatype = SYMBOL_DATATYPE_DOUBLE;
	newnode->text = calloc(strlen(text)+1, sizeof(char));
	strcpy(newnode->text, text);
	newnode->next = Table[address];
	Table[address] = newnode;
	
	return newnode;
}

void hashCheckUndeclared(){
	int i;
	Hash_Node *node;
	for(i = 0; i< HASH_SIZE; i++){
		for(node = Table[i]; node; node = node->next){
			if(node->type == SYMBOL_IDENTIFIER){
				fprintf(stderr, "ERRO semantico: variavel '%s' nao foi declarada.\n", node->text);			
			}	
		}
	}
}

Hash_Node* makeTemp(){
	static int serialNumber = 0;
	static char buffer[128];

	sprintf(buffer, "Temporary_%d", serialNumber++);
	fprintf(stderr, "Temporary_%d\n", serialNumber-1);
	return hashInsert(SYMBOL_TEMP, buffer);
}

Hash_Node* makeLabel(){
	static int serialNumber = 0;
	static char buffer[128];

	sprintf(buffer, "Label_%d", serialNumber++);
	return hashInsert(SYMBOL_IDENTIFIER, buffer);
}

void asmAddTemp(){
	int i;
	FILE* fout = fopen("asm.s", "w");
	for(i=0;i<HASH_SIZE;i++)
	{	
		Hash_Node* aux;
		for(aux = Table[i]; aux; aux = aux->next){
			if(aux->type == SYMBOL_TEMP) {
				fprintf(fout, "\t.globl	_%s\n"
				"\t.data\n"
				"\t.type	_%s, @object\n"
				"\t.size	_%s, 4\n"
				"_%s:\n" 				
				"\t.long 0\n" , aux->text, aux->text, aux->text, aux->text);
			}		
		}
	}	

	fclose(fout);
}

void asmAddImm(){
	int i;
	FILE* fout = fopen("asm.s", "a");
	for(i=0;i<HASH_SIZE;i++)
	{	
		Hash_Node* aux;
		for(aux = Table[i]; aux; aux = aux->next){
			if((aux->type == SYMBOL_LIT_INT || aux->type == SYMBOL_LIT_REAL) && (aux->datatype == SYMBOL_DATATYPE_BYTE ||aux->datatype == SYMBOL_DATATYPE_SHORT || aux->datatype == SYMBOL_DATATYPE_LONG))
			{ 
				    fprintf(fout, "\t.globl	_%s\n"
				    "\t.data\n"
				    "\t.type	_%s, @object\n"
				    "\t.size	_%s, 4\n"
				    "_%s:\n" ,aux->text, aux->text, aux->text, aux->text);
                		    if(aux->datatype == SYMBOL_DATATYPE_FLOAT || aux->datatype == SYMBOL_DATATYPE_DOUBLE)
			            {
					    fprintf(fout, "\t.float	%s\n", aux->text);
			   	    }
				    else if(aux->datatype == SYMBOL_DATATYPE_BYTE ||aux->datatype == SYMBOL_DATATYPE_SHORT || aux->datatype == SYMBOL_DATATYPE_LONG){
				    	fprintf(fout, "\t.long	%s\n", aux->text);
			    	    }
			}
		}
	}	

	fclose(fout);
}

