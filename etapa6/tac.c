/* 
	ETAPA 6 - TRABALHO DE COMPILADORES
	Gabriel Zillmer e Rodrigo dal Ri 
*/
#include <stdio.h>
#include <stdlib.h>
#include "tac.h"

TAC* tacCreate(int type, Hash_Node *res, Hash_Node *op1, Hash_Node *op2)
{
	TAC *n = (TAC*) calloc(1, sizeof(TAC));
	n->type = type;
	n->res = res;
	n->op1 = op1;
	n->op2 = op2;
	n->prev = 0;
	n->next = 0;	
	return n;
}

TAC* tacJoin(TAC* l1, TAC* l2)
{
	TAC* tac;
	if(!l1) return l2;
	if(!l2) return l1;
	tac = l2;
	while(tac->prev){
		tac = tac->prev;	
	}
	tac->prev = l1;
	return l2;
}

void tacPrintBack(TAC *last)
{
	fprintf(stderr, "\n ---Imprimindo codigo gerado---\n");
	
	TAC *tac;

	for(tac = last; tac; tac = tac->prev){
		tacPrintOne(tac);
	}
}

void tacPrintFoward(TAC* first)
{
	fprintf(stderr, "\n ---Imprimindo codigo gerado---\n");
	
	TAC *tac;

	for(tac = first; tac; tac = tac->next){
		tacPrintOne(tac);
	}
	
}

TAC* tacReverse(TAC* tac)
{
	TAC* t;
	for(t = tac; t->prev; t = t->prev)
		t->prev->next = t;
	return t;
}

void tacPrintOne(TAC *tac)
{
		if(tac->type == TAC_SYMBOL) return;
		fprintf(stderr, "TAC(");
		switch(tac->type){
			case TAC_SYMBOL: fprintf(stderr, "TAC_SYMBOL"); break;
			case TAC_ADD: fprintf(stderr, "TAC_ADD"); break;//
			case TAC_SUB: fprintf(stderr, "TAC_SUB"); break;//
			case TAC_MUL: fprintf(stderr, "TAC_MUL"); break;//
			case TAC_DIV: fprintf(stderr, "TAC_DIV"); break;//
			case TAC_L: fprintf(stderr, "TAC_L"); break;//
			case TAC_G: fprintf(stderr, "TAC_G"); break;//
			case TAC_LE: fprintf(stderr, "TAC_LE"); break;//
			case TAC_GE: fprintf(stderr, "TAC_GE"); break;//
			case TAC_EQ: fprintf(stderr, "TAC_EQ"); break;//
			case TAC_NE: fprintf(stderr, "TAC_NE"); break;//
			case TAC_AND: fprintf(stderr, "TAC_AND"); break;//
			case TAC_OR: fprintf(stderr, "TAC_OR"); break;//
			case TAC_NOT: fprintf(stderr, "TAC_NOT"); break;
			case TAC_MOVE: fprintf(stderr, "TAC_MOVE"); break;//
			case TAC_READ: fprintf(stderr, "TAC_READ"); break;//
			case TAC_RET: fprintf(stderr, "TAC_RET"); break;//
			case TAC_IFZ: fprintf(stderr, "TAC_IFZ"); break;//
			case TAC_LABEL: fprintf(stderr, "TAC_LABEL"); break;//
			case TAC_JUMP: fprintf(stderr, "TAC_JUMP"); break;//
			case TAC_PRINT: fprintf(stderr, "TAC_PRINT"); break;//
			case TAC_PARPOP: fprintf(stderr, "TAC_PARPOP"); break;//
			case TAC_FUNCALL: fprintf(stderr, "TAC_FUNCALL"); break;//
			case TAC_BEGINFUN: fprintf(stderr, "TAC_BEGINFUN"); break;//
			case TAC_ENDFUN: fprintf(stderr, "TAC_ENDFUN"); break;//
			case TAC_AREAD: fprintf(stderr, "TAC_AREAD"); break;//
			case TAC_AWRITE: fprintf(stderr, "TAC_AWRITE"); break;//			
			case TAC_AINIPUSH: fprintf(stderr, "TAC_AINIPUSH"); break;
			case TAC_ASIZE: fprintf(stderr, "TAC_ASIZE"); break;
			case TAC_PARPUSH: fprintf(stderr, "TAC_PARPUSH"); break;//
			
			default: fprintf(stderr, "TAC_UNKNOWN"); break;
		}
		if(tac->res) fprintf(stderr, ",%s", tac->res->text); else fprintf(stderr, ",0");
		if(tac->op1) fprintf(stderr, ",%s", tac->op1->text); else fprintf(stderr, ",0");
		if(tac->op2) fprintf(stderr, ",%s", tac->op2->text); else fprintf(stderr, ",0");
		fprintf(stderr, ")\n");
}

TAC* tacGenerate(ASTREE *node)
{
	int i = 0;
	TAC *code[MAX_SONS];
	TAC *result = 0;

	if(!node) return 0;
	
	for(i = 0; i < MAX_SONS; i++)
	{
		code[i] = tacGenerate(node->son[i]);
	}

	switch(node->type)
	{
		case ASTREE_SYMBOL: result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0); break;
		case ASTREE_ADD: result = tacJoin(code[0],tacJoin(code[1],tacCreate(TAC_ADD, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0))); break;
		case ASTREE_SUB: result = tacJoin(code[0],tacJoin(code[1],tacCreate(TAC_SUB, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0))); break; 
		case ASTREE_MUL: result = tacJoin(code[0],tacJoin(code[1],tacCreate(TAC_MUL, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0))); break; 
		case ASTREE_DIV: result = tacJoin(code[0],tacJoin(code[1],tacCreate(TAC_DIV, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0))); break; 
		case ASTREE_L: result = tacJoin(code[0],tacJoin(code[1],tacCreate(TAC_L, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0))); break;
		case ASTREE_G: result = tacJoin(code[0],tacJoin(code[1],tacCreate(TAC_G, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0))); break; 
		case ASTREE_LE: result = tacJoin(code[0],tacJoin(code[1],tacCreate(TAC_LE, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0))); break; 
		case ASTREE_GE: result = tacJoin(code[0],tacJoin(code[1],tacCreate(TAC_GE, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0))); break; 
		case ASTREE_EQ: result = tacJoin(code[0],tacJoin(code[1],tacCreate(TAC_EQ, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0))); break;
		case ASTREE_NE: result = tacJoin(code[0],tacJoin(code[1],tacCreate(TAC_NE, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0))); break; 
		case ASTREE_AND: result = tacJoin(code[0],tacJoin(code[1],tacCreate(TAC_AND, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0))); break; 
		case ASTREE_OR: result = tacJoin(code[0],tacJoin(code[1],tacCreate(TAC_OR, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0))); break; 
		case ASTREE_NOT: result = tacJoin(tacJoin(code[0], code[1]),tacCreate(TAC_NOT, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break; 
		case ASTREE_ATR: result = tacJoin(code[0], tacCreate(TAC_MOVE, node->symbol, code[0]?code[0]->res:0, 0)); break;
		case ASTREE_READ: result = tacCreate(TAC_READ, node->symbol, 0, 0); break;
		case ASTREE_RETURN: result = tacJoin(code[0], tacCreate(TAC_RET, node->symbol, code[0]?code[0]->res:0, 0)); break;
		case ASTREE_IF: result = makeIfThenElse(code[0], code[1], 0); break;
		case ASTREE_ELSE: result = makeIfThenElse(code[0], code[1], code[2]); break;
		case ASTREE_WHILE: result = makeWhile(code[0], code[1]); break;
		case ASTREE_PRINTL: result = tacJoin(tacCreate(TAC_PRINT, code[0]?code[0]->res:0, 0, 0), code[1]); break;
		case ASTREE_FUNCALL: result = tacJoin(code[0], tacCreate(TAC_FUNCALL, makeTemp(), node->symbol, 0)); break;
		case ASTREE_PARCALLL: result = tacJoin(code[1], tacCreate(TAC_PARPUSH, code[0]?code[0]->res:0, 0, 0)); break;
		case ASTREE_FUNDEF: result = makeFunction(tacCreate(TAC_SYMBOL, node->symbol, 0, 0), code[1], code[2]); break;
		case ASTREE_PARAM: result = tacCreate(TAC_PARPOP, node->symbol, 0, 0); break;
		case ASTREE_PARL: result = tacJoin(code[0], code[1]); break;
		

		//NÃO SEI SE PRECISA
		/*case ASTREE_ARRAY_READ: result = tacCreate(TAC_AREAD, makeTemp(), node->symbol, code[0]?code[0]->res:0); break;
		case ASTREE_ARRAY_WRITE: result = tacJoin(code[1], tacCreate(TAC_AWRITE, node->symbol, code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
		case ASTREE_VARINI: result = code[0]; break;
		case ASTREE_INTL: result = tacJoin(code[0], tacCreate(TAC_AINIPUSH, node->symbol, 0, 0)); break;
		case ASTREE_ARRINI: result = tacJoin(code[0], tacCreate(TAC_ASIZE, node->symbol, 0, 0)); break;
		*/

		default: result = tacJoin(tacJoin(tacJoin(code[0], code[1]), code[2]), code[3]) ; break;
	}

	return result;
}

TAC* makeWhile(TAC* code0, TAC* code1)
{
	TAC* whileTAC;
	TAC *whileLabelTAC, *jumpLabelTAC;

	Hash_Node *newWhileLabel = makeLabel(), *newJumpLabel = makeLabel();
	TAC* jumpTAC = tacCreate(TAC_JUMP, newWhileLabel, 0, 0);
	whileTAC = tacCreate(TAC_IFZ, newJumpLabel, code0?code0->res:0, 0);

	whileLabelTAC = tacCreate(TAC_LABEL, newWhileLabel, 0, 0);
	jumpLabelTAC = tacCreate(TAC_LABEL, newJumpLabel, 0, 0);	

	return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(whileLabelTAC, code0), whileTAC), code1),jumpTAC), jumpLabelTAC);
}

TAC* makeFunction(TAC* symbol, TAC* par, TAC* code)
{
	return tacJoin(tacJoin(tacJoin( tacCreate(TAC_BEGINFUN, symbol->res, 0, 0), par) , code ), tacCreate(TAC_ENDFUN, symbol->res, 0, 0));
}

TAC* makeIfThenElse(TAC* code0, TAC* code1, TAC* code2)
{
	TAC* ifTAC;
	TAC* jumpTAC;
	TAC* ifLabelTAC;
	TAC* elseLabelTAC = 0;
	
	Hash_Node* newIfLabel = makeLabel();
	Hash_Node* newElseLabel = 0;

	if(code2)
	{
		newElseLabel = makeLabel();		
		jumpTAC = tacCreate	(TAC_JUMP, newElseLabel, 0, 0);
		elseLabelTAC = tacCreate(TAC_LABEL, newElseLabel, 0, 0);
	}
	
	ifTAC = tacCreate(TAC_IFZ, newIfLabel, code0?code0->res:0, 0);
	ifLabelTAC = tacCreate(TAC_LABEL, newIfLabel, 0, 0);

	if(code2) 
		return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(code0, ifTAC), code1), jumpTAC),ifLabelTAC),code2), elseLabelTAC);	
	else 
		return tacJoin(tacJoin(tacJoin(code0, ifTAC), code1),ifLabelTAC);
}




void asmAddPrintData()
{
	FILE *fout = fopen("asm.s", "a");
	fprintf(fout, "\t.section	.rodata\n"
			".LC0:\n"
			"\t.string	\"%%d\"\n");
	fprintf(fout, "\t.section	.rodata\n"
			".LC1:\n"
			"\t.string	\"%%s\"\n");
	fclose(fout);
}

void asmAddString(TAC *first)
{
    FILE *fout = fopen("asm.s", "a");
    TAC* tac;
    int numLC = 2;
    char* lable=0;

    for(tac = first; tac; tac = tac->next){
		if(tac->type == TAC_SYMBOL) continue;

        
    switch(tac->type){
        case TAC_PRINT:
        	sprintf(lable, ".LC%d", numLC);
	        fprintf(fout, "%s:\n \t.string \"%s\" \n", lable, tac->res->text);
                numLC++;
		break;
    default:
		printf("=(\n");
		break;
    }
    }
    fclose(fout);
}


void asmGen(TAC *first)
{
	
	FILE *fout = fopen("asm.s", "a");
	TAC* tac;
	int labelNmbr = 2;
    	int lableLC = 2;
	char parReg[6][4]  = {{"edi\0"}, {"esi\0"},{"edx\0"}, {"ecx\0"}, {"r8d\0"}, {"r9d\0"}};
	int parNmbr1 = 0, parNmbr2 = 0;
	int aux = 0;
	
	for(tac = first; tac; tac = tac->next){
		if(tac->type == TAC_SYMBOL) continue;   

	switch(tac->type){
		case TAC_ADD: fprintf(fout, "\tmovl	_%s(%%rip), %%edx\n"
									"\tmovl	_%s(%%rip), %%eax\n"
									"\taddl	%%eax, %%edx\n"
									"\tmovl	%%edx, _%s(%%rip)\n", tac->op1->text,tac->op2->text,tac->res->text); break; 

       

		case TAC_SUB: fprintf(fout, "\tmovl	_%s(%%rip), %%edx\n"
									"\tmovl	_%s(%%rip), %%eax\n"
									"\tsubl	%%eax, %%edx\n"
									"\tmovl	%%edx, _%s(%%rip)\n", tac->op1->text,tac->op2->text,tac->res->text); break;	

		case TAC_DIV: fprintf(fout, "\tmovl	_%s(%%rip), %%eax\n"
									"\tmovl	_%s(%%rip), %%ecx\n"
									"\tcltd\n"
									"\tidivl	%%ecx\n"
									"\tmovl	%%eax, _%s(%%rip)\n", tac->op1->text,tac->op2->text,tac->res->text); break;

                       if(aux == 0){
                        fprintf(fout, "\tmovl	_%s(%%rip), %%eax\n"
									"\tmovl	_%s(%%rip), %%ecx\n"
									"\tcltd\n"
									"\tidivl	%%ecx\n"
									"\tmovl	%%eax, _%s(%%rip)\n", tac->op1->text,tac->op2->text,tac->res->text); break;
                      }else{
                        fprintf(fout, "\tmovl	_%s(%%rip), %%edx\n"
									  "\tmovl	_%s(%%rip), %%eax\n"       
                                      "\tshr $%d, %%edx\n"                                    
									  "\tmovl	%%edx, _%s(%%rip)\n", tac->op1->text,tac->op2->text, aux, tac->res->text); break;
                      }

		case TAC_MUL: 
                      if(aux == 0){
                        fprintf(fout, "\tmovl	_%s(%%rip), %%edx\n"
									  "\tmovl	_%s(%%rip), %%eax\n"       
                                      "\timull %%eax, %%edx\n"
									  "\tmovl	%%edx, _%s(%%rip)\n", tac->op1->text,tac->op2->text,tac->res->text); break;
                      }else{
                        fprintf(fout, "\tmovl	_%s(%%rip), %%edx\n"
									  "\tmovl	_%s(%%rip), %%eax\n"       
                                      "\tshl $%d, %%edx\n"
                                      
									  "\tmovl	%%edx, _%s(%%rip)\n", tac->op1->text,tac->op2->text, aux, tac->res->text); break;
                      }
	
		case TAC_EQ: fprintf(fout, "\tmovl	_%s(%%rip), %%edx\n"
									"\tmovl	_%s(%%rip), %%eax\n"
									"\tcmpl	%%eax, %%edx\n"
									"\tsete	%%al\n"
									"\tmovzbl	%%al, %%eax\n"
									"\tmovl	%%eax, _%s(%%rip)\n", tac->op1->text,tac->op2->text,tac->res->text); break;	

		case TAC_NE: fprintf(fout, "\tmovl	_%s(%%rip), %%edx\n"
									"\tmovl	_%s(%%rip), %%eax\n"
									"\tcmpl	%%eax, %%edx\n"
									"\tsetne	%%al\n"
									"\tmovzbl	%%al, %%eax\n"
									"\tmovl	%%eax, _%s(%%rip)\n", tac->op1->text,tac->op2->text,tac->res->text); break;	

		case TAC_OR: fprintf(fout, "\tmovl	_%s(%%rip), %%eax\n"
									"\ttestl	%%eax, %%eax\n"
									"\tjne	.L%d\n"
									"\tmovl	_%s(%%rip), %%eax\n"
									"\ttestl	%%eax, %%eax\n"
									"\tje	.L%d\n"
									".L%d:\n"
									"\tmovl	$1, %%eax\n" //modifique para poder compilar %_1
									"\tjmp	.L%d\n"
									".L%d:\n"
									"\tmovl	$0, %%eax\n" //modifique para poder compilar %_0
									".L%d:\n"
									"\tmovl	%%eax, _%s(%%rip)\n", tac->op1->text, labelNmbr, tac->op2->text, labelNmbr+1, labelNmbr, labelNmbr+2, labelNmbr+1, labelNmbr+2, tac->res->text);
									labelNmbr += 3;
									break;		

		case TAC_AND: fprintf(fout, "\tmovl	_%s(%%rip), %%eax\n"
									"\ttestl	%%eax, %%eax\n"
									"\tje	.L%d\n"
									"\tmovl	_%s(%%rip), %%eax\n"
									"\ttestl	%%eax, %%eax\n"
									"\tje	.L%d\n"
									"\tmovl	$1, %%eax\n"  //modifique para poder compilar %_1
									"\tjmp	.L%d\n"
									".L%d:\n"
									"\tmovl	$0, %%eax\n" //modifique para poder compilar %_0
									".L%d:\n"
									"\tmovl	%%eax, _%s(%%rip)\n", tac->op1->text, labelNmbr, tac->op2->text, labelNmbr, labelNmbr+1, labelNmbr, labelNmbr+1, tac->res->text);
									labelNmbr += 2;
									break;
		case TAC_NOT: 

				break;
		case TAC_G: fprintf(fout, "\tmovl	_%s(%%rip), %%edx\n"
									"\tmovl	_%s(%%rip), %%eax\n"
									"\tcmpl	%%eax, %%edx\n"
									"\tsetg	%%al\n"
									"\tmovzbl	%%al, %%eax\n"
									"\tmovl	%%eax, _%s(%%rip)\n", tac->op1->text, tac->op2->text, tac->res->text);
									break;

		case TAC_L: fprintf(fout, "\tmovl	_%s(%%rip), %%edx\n"
									"\tmovl	_%s(%%rip), %%eax\n"
									"\tcmpl	%%eax, %%edx\n"
									"\tsetl	%%al\n"
									"\tmovzbl	%%al, %%eax\n"
									"\tmovl	%%eax, _%s(%%rip)\n", tac->op1->text, tac->op2->text, tac->res->text);
									break;

		case TAC_GE: fprintf(fout, "\tmovl	_%s(%%rip), %%edx\n"
									"\tmovl	_%s(%%rip), %%eax\n"
									"\tcmpl	%%eax, %%edx\n"
									"\tsetge	%%al\n"
									"\tmovzbl	%%al, %%eax\n"
									"\tmovl	%%eax, _%s(%%rip)\n", tac->op1->text, tac->op2->text, tac->res->text);
									break;

		case TAC_LE: fprintf(fout, "\tmovl	_%s(%%rip), %%edx\n"
									"\tmovl	_%s(%%rip), %%eax\n"
									"\tcmpl	%%eax, %%edx\n"
									"\tsetle	%%al\n"
									"\tmovzbl	%%al, %%eax\n"
									"\tmovl	%%eax, _%s(%%rip)\n", tac->op1->text, tac->op2->text, tac->res->text);
									break;

		case TAC_BEGINFUN: fprintf(fout, "\t.text\n"
									"\t.globl %s\n"
									"\t.type	%s, @function\n" 
									"%s:\n"
									"\tpushq	%%rbp\n"
									"\tmovq	%%rsp, %%rbp\n",  tac->res->text, tac->res->text, tac->res->text);
									break;
	
		case TAC_ENDFUN: fprintf(fout, "\tpopq	%%rbp\n"
									"\tret\n");
									parNmbr2 = 0;
									break;

		case TAC_FUNCALL: fprintf(fout, "\tcall	%s\n"
										"\tmovl	%%eax, _%s(%%rip)\n" , tac->op1->text, tac->res->text);
										parNmbr1 = 0;
									break;

		case TAC_RET: fprintf(fout, "\tmovl	_%s(%%rip), %%eax\n" , tac->op1->text);
									break;

		case TAC_LABEL: fprintf(fout, ".%s:\n" , tac->res->text);
									break;

		case TAC_JUMP: fprintf(fout, "\tjmp	.%s\n" , tac->res->text);
									break;

		case TAC_MOVE: fprintf(fout, "\tmovl	_%s(%%rip), %%eax\n"
									"\tmovl	%%eax, _%s(%%rip)\n" , tac->op1->text, tac->res->text);
									break;

		case TAC_IFZ: fprintf(fout, "\tmovl	_%s(%%rip), %%eax\n"
									"\ttestl	%%eax, %%eax\n"
									"\tjne	.L%d\n"
									"\tjmp	.%s\n"
									".L%d:", tac->op1->text, labelNmbr, tac->res->text, labelNmbr);
									labelNmbr++;
									break;

		case TAC_PARPOP: fprintf(fout, "\tmovl	%%%s, %%eax\n"
									   "\tmovl	%%eax, _%s(%%rip)\n" , parReg[parNmbr2++], tac->res->text);
									break;

		case TAC_PARPUSH: fprintf(fout, "\tmovl	_%s(%%rip), %%eax\n"
										"\tmovl	%%eax, %%%s\n", tac->res->text, parReg[parNmbr1++]);
									break;


		case TAC_AREAD: fprintf(fout, "\tmovl	_%s(%%rip), %%eax\n"
									"\tcltq\n"
									"\tmovl	_%s(,%%rax,4), %%eax\n"
									"\tmovl	%%eax, _%s(%%rip)\n" , tac->op2->text, tac->op1->text, tac->res->text);
									break;

		case TAC_AWRITE: fprintf(fout, "\tmovl	_%s, %%eax\n"
									"\tmovl	_%s(%%rip), %%edx\n"
									"\tcltq\n"
									"\tmovl	%%edx, _%s(,%%rax,4)\n", tac->op1->text, tac->op2->text, tac->res->text);
									break;

        	case TAC_READ: fprintf(fout, "\tmovl	$_%s, %%esi\n"
									"\tmovl	$.LC0, %%edi\n"
									"\tcall	__isoc99_scanf\n", tac->res->text);
									break;

		case TAC_PRINT: 
						if(tac->res->text[0] == '\"'){ 
                            printf("STRING\n");
                            fprintf(fout, "\tmovl	$.LC%d, %%esi\n"
									"\tmovl	$.LC1, %%edi\n"
									"\tcall	printf\n", lableLC);
                            lableLC++; break;
                        }else{			
                            printf("VARIAVEL\n");				
							fprintf(fout, "\tmovl	_%s(%%rip), %%eax\n" 
									"\tmovl	%%eax, %%esi\n"
									"\tmovl	$.LC0, %%edi\n"
									"\tcall	printf\n", tac->res->text);
                             
                            break;
                          }


		}

	}
	fclose(fout);
	
}

