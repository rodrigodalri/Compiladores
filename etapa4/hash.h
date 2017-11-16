/* 
	ETAPA 4 - TRABALHO DE COMPILADORES
	Gabriel Zillmer e Rodrigo dal Ri 
*/
#ifndef HASH_H
#define HASH_H

#define HASH_SIZE 999

#define SYMBOL_IDENTIFIER 10
#define SYMBOL_VAR 11
#define SYMBOL_ARR 12
#define SYMBOL_FUN 13

#define SYMBOL_LIT_INT 100
#define SYMBOL_LIT_REAL 101
#define SYMBOL_LIT_CHAR 102
#define SYMBOL_LIT_STRING 103

#define SYMBOL_DATATYPE_BYTE 200
#define SYMBOL_DATATYPE_SHORT 201
#define SYMBOL_DATATYPE_LONG 202
#define SYMBOL_DATATYPE_FLOAT 203
#define SYMBOL_DATATYPE_DOUBLE 204

typedef struct hash_struct
{
	int type;
	int datatype;
	int numparam;
	char* text;
	struct hash_struct *next; 
}Hash_Node;

Hash_Node* Table[HASH_SIZE];

void hashInit();
void hashPrint();

int hashAddress(char* text);

Hash_Node* hashFind(char* text);
Hash_Node* hashInsert(int type, char* text);

void hashCheckUndeclared();

#endif

