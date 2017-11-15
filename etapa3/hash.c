/* 
	ETAPA 3 - TRABALHO DE COMPILADORES
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
		Table[i] = 0;
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
}

Hash_Node* hashInsert(int type, char* text)
{
	Hash_Node* newNode;
	
	newNode = hashFind(text);
	
	if(newNode != NULL){
		if(type == newNode->type){		
			return newNode;
		}
	}
	int address = hashAddress(text);
	
	if(Table[address] == 0) 
	{
		newNode = calloc(1, sizeof(Hash_Node));
		newNode->type = type;
		newNode->text = calloc(strlen(text)+1,sizeof(char));
		strcpy(newNode->text,text);
		newNode->next = NULL;
		Table[address] = newNode;
	}else 
	{
		Hash_Node* chainedNode = Table[address];
		while(chainedNode->next != NULL)
		{
			chainedNode = chainedNode->next;
		}
		newNode = calloc(1, sizeof(Hash_Node));
		newNode->type = type;
		newNode->text = calloc(strlen(text)+1,sizeof(char));
		strcpy(newNode->text,text);
		newNode->next = NULL;
		chainedNode->next = newNode;
	}
	
	return newNode;
}
