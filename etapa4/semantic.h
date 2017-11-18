/* 
	ETAPA 4 - TRABALHO DE COMPILADORES
	Gabriel Zillmer e Rodrigo dal Ri
*/

#include "astree.h"

#ifndef SEMANTIC_H
#define SEMANTIC_H

void checkSemantic(ASTREE* node);

void setTypes(ASTREE* node); 
void checkUndeclared(void);
void checkUsage(ASTREE* node);
void checkOperands(ASTREE* node);

int countNumParam(ASTREE* node);
int checkNumParam(ASTREE* node);
int checkTypeParam(ASTREE* node);




#endif
