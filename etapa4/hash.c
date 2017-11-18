/* 
	ETAPA 4 - TRABALHO DE COMPILADORES
	Gabriel Zillmer e Rodrigo dal Ri 
*/

#include "hash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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
     
	printf("id: %d ", i);
	printf("Type: %d ", Table[i]->type);
	printf("DataType: %d ", Table[i]->datatype);
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

