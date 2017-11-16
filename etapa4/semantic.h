/* 
	ETAPA 4 - TRABALHO DE COMPILADORES
	Gabriel Zillmer e Rodrigo dal Ri
*/

#include "astree.h"

#ifndef SEMANTIC_H
#define SEMANTIC_H

void checkSemantic(ASTREE* node);

void SetTypes(ASTREE* node); 
void CheckUndeclared(void);
void CheckUsage(ASTREE* node);
void CheckOperands(ASTREE* node);





#endif
