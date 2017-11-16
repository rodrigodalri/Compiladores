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
int greaterDatatype(int a, int b);

void checkFunCall(ASTREE* node);
void setFunParam(ASTREE* node);
void checkReturnFun(ASTREE* node, ASTREE* nodefunc);






#endif
