/* 
	ETAPA 2 - TRABALHO DE COMPILADORES
	Gabriel Zillmer e Rodrigo dal Ri 
*/

#define HASH_SIZE 9999

typedef struct hash_struct
{
	int type;
	char* text;
	struct hash_struct *next; 
}Hash_Node;

Hash_Node* Table[HASH_SIZE];

void hashInit();
void hashPrint();

int hashAddress(char* text);

Hash_Node* hashFind(char* text);
Hash_Node* hashInsert(int type, char* text);

