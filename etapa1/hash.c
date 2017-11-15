/* 
	ETAPA 1 - TRABALHO DE COMPILADORES
	Gabriel Zillmer e Rodrigo dal Ri 
*/

#include "hash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void hashInit(){
	int i;
	for(i=0;i<=HASH_SIZE;i++){
		Table[i] = 0;
	}
}

void hashPrint(){
	int i;
	printf("\n");
	printf("PRINT\n");
	for(i=0;i<=HASH_SIZE;i++){	
		if(Table[i] != 0){
			printf("id: %d ", i);
			printf("Tok: %d ", Table[i]->type);
			printf("Text: %s\n", Table[i]->text);
			Hash_Node* chainedNode = Table[i];
			while(chainedNode->next != NULL){
				chainedNode = chainedNode->next;
				printf("id: %d ", i);
				printf("Tok: %d ", chainedNode->type);
				printf("Text: %s\n", chainedNode->text);
			}
		}
	}
	printf("END\n");
	printf("\n");

}

int hashAddress(char* text){
	int i;
	int address = 1;
	for(i=0;i<strlen(text);i++)
		address = (address * text[i])%HASH_SIZE + 1;
	return address - 1;
}

Hash_Node* hashFind(char* text){
	int address = hashAddress(text);
	Hash_Node* chainedNode = Table[address];

	while(chainedNode != NULL)	{
		int a = strcmp(text, chainedNode->text);
		if(a == 0)
			return chainedNode;
		else
			chainedNode = chainedNode->next;	
	}
}

Hash_Node* hashInsert(int type, char* text){
	Hash_Node* newNode;
	newNode = hashFind(text);
	
	if(newNode != NULL){
		if(type == newNode->type){		
			return newNode;
		}
	}
	
	int address = hashAddress(text);
	
	if(Table[address] == 0){
		newNode = calloc(1, sizeof(Hash_Node));
		newNode->type = type;
		newNode->text = calloc(strlen(text)+1,sizeof(char));
		strcpy(newNode->text,text);
		newNode->next = NULL;
		Table[address] = newNode;
	}else{
		Hash_Node* chainedNode = Table[address];
		while(chainedNode->next != NULL){
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
