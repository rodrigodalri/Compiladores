/* 
	ETAPA 5 - TRABALHO DE COMPILADORES
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

#define SYMBOL_DATATYPE_BYTE 201
#define SYMBOL_DATATYPE_SHORT 202
#define SYMBOL_DATATYPE_LONG 203

#define SYMBOL_DATATYPE_FLOAT 204
#define SYMBOL_DATATYPE_DOUBLE 205

#define SYMBOL_DATATYPE_BOOL 206

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

Hash_Node* makeTemp();
Hash_Node* makeLabel();

#endif

