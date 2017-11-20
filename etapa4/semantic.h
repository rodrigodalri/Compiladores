/* 
	ETAPA 4 - TRABALHO DE COMPILADORES
	Gabriel Zillmer e Rodrigo dal Ri
*/

#include "astree.h"

#ifndef SEMANTIC_H
#define SEMANTIC_H

int checkSemantic(ASTREE* node);

void setTypes(ASTREE* node); 
void checkUndeclared(void);
void checkUsage(ASTREE* node);
void checkOperands(ASTREE* node);

void checkReturn(ASTREE *nodefunc, ASTREE *node);
void checkTypeParam(ASTREE* nodecall, ASTREE* nodedef);
void linkStart(ASTREE *node, ASTREE *root);
ASTREE *search(ASTREE *node, char *name);
int countNumParam(ASTREE* node);
void checkNumParam(ASTREE* node);
int greaterDatatype(int a, int b);

#endif