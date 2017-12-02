/* 
	ETAPA 5 - TRABALHO DE COMPILADORES
	Gabriel Zillmer e Rodrigo dal Ri 
*/

#include <stdio.h>
#include <stdlib.h>

#include "astree.h"

extern FILE* yyin;
extern FILE* file();
extern int yylex();
extern int isRunning();
extern int getLineNumber();
extern int yyparse();
extern void initMe();
extern void hashPrint();
extern ASTREE* getAst();
extern void resultSemantic();

FILE *out;

void uncompile(ASTREE *ast){
 
  	if(!ast) return;
	if(ast){	
		
		switch(ast->type){         
		
			case ASTREE_SYMBOL:
                		fprintf(out, "%s", ast->symbol->text);
                		break;
	  		case ASTREE_AND:
                		uncompile(ast->son[0]); fprintf(out,"&&"); uncompile(ast->son[1]);
                		break;
            		case ASTREE_OR:
                		uncompile(ast->son[0]); fprintf(out,"||"); uncompile(ast->son[1]);
                		break;
            		case ASTREE_ADD:
                		uncompile(ast->son[0]); fprintf(out,"+"); uncompile(ast->son[1]);
                		break;
            		case ASTREE_SUB:
                		uncompile(ast->son[0]); fprintf(out,"-"); uncompile(ast->son[1]);
                		break;
            		case ASTREE_MUL:
                		uncompile(ast->son[0]); fprintf(out,"*"); uncompile(ast->son[1]);
                		break;
            		case ASTREE_DIV:
                		uncompile(ast->son[0]); fprintf(out,"/"); uncompile(ast->son[1]);
                		break;
            		case ASTREE_L:
                		uncompile(ast->son[0]); fprintf(out,"<"); uncompile(ast->son[1]);
                		break;
            		case ASTREE_G:
                		uncompile(ast->son[0]); fprintf(out,">"); uncompile(ast->son[1]);
                		break;
            		case ASTREE_LE:
                		uncompile(ast->son[0]); fprintf(out,"<="); uncompile(ast->son[1]);
                		break;
            		case ASTREE_GE:
                		uncompile(ast->son[0]); fprintf(out,">="); uncompile(ast->son[1]);
                		break;
            		case ASTREE_EQ:
                		uncompile(ast->son[0]); fprintf(out,"=="); uncompile(ast->son[1]);
                		break;
            		case ASTREE_NE:
                		uncompile(ast->son[0]); fprintf(out,"!="); uncompile(ast->son[1]);
                		break;
			case ASTREE_NOT:
                		fprintf(out,"!");uncompile(ast->son[0]);  
                		break;
            		case ASTREE_READ:
                		fprintf(out,"read > "); fprintf(out,"%s", ast->symbol->text);
                		break;
            		case ASTREE_RETURN:
               			fprintf(out,"return "); uncompile(ast->son[0]);
                		break;
            		case ASTREE_WHILE:
                		fprintf(out,"while("); uncompile(ast->son[0]); fprintf(out,")"); uncompile(ast->son[1]);
                		break;
			case ASTREE_FUNDEF:
               			fprintf(out,"("); uncompile(ast->son[0]); fprintf(out,")"); fprintf(out,"%s", ast->symbol->text); fprintf(out,"("); uncompile(ast->son[1]); fprintf(out,")"); uncompile(ast->son[2]);         
                		break;    
            		case ASTREE_FUNCALL:
                		fprintf(out,"%s", ast->symbol->text); fprintf(out,"("); uncompile(ast->son[0]); fprintf(out,")");
                		break;
 			case ASTREE_PARENTHESIS:
                		fprintf(out,"("); uncompile(ast->son[0]); fprintf(out,")");
                		break;
            		case ASTREE_BRACES:
                		fprintf(out,"{\n"); uncompile(ast->son[0]); fprintf(out,"}");
                		break;
			case ASTREE_PARAM:
                 		fprintf(out,"%s:", ast->symbol->text); uncompile(ast->son[0]);
                		break; 
			case ASTREE_ATR:
                 		fprintf(out,"%s", ast->symbol->text); fprintf(out,"="); uncompile(ast->son[0]);
                		break;
			case ASTREE_ARRAY_WRITE:
                		fprintf(out, "%s", ast->symbol->text); fprintf(out, "["); uncompile(ast->son[0]);fprintf(out, "]"); fprintf(out, "="); uncompile(ast->son[1]);
                		break;
			case ASTREE_ARRAY_READ:
                		fprintf(out,"%s", ast->symbol->text); fprintf(out,"["); uncompile(ast->son[0]); fprintf(out,"]");
                		break;
   			case ASTREE_PRINT:
                		fprintf(out,"print "); uncompile(ast->son[0]); 
                		break;
			case ASTREE_PRINTL:
                		if(ast->son[1] != NULL){
                    			uncompile(ast->son[0]); fprintf(out,","); uncompile(ast->son[1]);
                		}else
                   	 		uncompile(ast->son[0]);
                		break;
 			case ASTREE_CMDL:
                		if(ast->son[1] != NULL){
                    			uncompile(ast->son[0]); fprintf(out,";\n"); uncompile(ast->son[1]);
                		}else
                    			uncompile(ast->son[0]);
                		break;
            		case ASTREE_DFNL:
							
					if(ast->son[1] != NULL)
						{
                    				uncompile(ast->son[0]); fprintf(out," \n"); uncompile(ast->son[1]);
                				}	
					else
                    				uncompile(ast->son[0]);
				
                		break;
            		case ASTREE_PARL:
                		if(ast->son[1] != NULL){
                    			uncompile(ast->son[0]); fprintf(out,","); uncompile(ast->son[1]);
                		}else
                    			uncompile(ast->son[0]);
                		break;
			case ASTREE_PARCALLL:
                		if(ast->son[1] != NULL){
                    			uncompile(ast->son[0]); fprintf(out,","); uncompile(ast->son[1]);
                		}else
                    			uncompile(ast->son[0]);
                		break;
            		case ASTREE_INTL:
				if(ast->son[1] != NULL){
                    			uncompile(ast->son[0]); fprintf(out," "); uncompile(ast->son[1]);
                		}else
                    			uncompile(ast->son[0]);
               	 		break;
			case ASTREE_VARINI:
                		fprintf(out,"%s", ast->symbol->text); fprintf(out,": "); uncompile(ast->son[0]); fprintf(out,"="); uncompile(ast->son[1]);fprintf(out,";"); uncompile(ast->son[2]);
               		 	break;
              		case ASTREE_BYTE:
                		fprintf(out,"byte");
                		break;
            		case ASTREE_SHORT:
                		fprintf(out,"short");
               	 		break;
            		case ASTREE_LONG:
                		fprintf(out,"long");
                		break;
            		case ASTREE_FLOAT:
                		fprintf(out,"float");
                		break;
            		case ASTREE_DOUBLE:
                		fprintf(out,"double");
                		break; 
			case ASTREE_IF:
                		fprintf(out,"if("); uncompile(ast->son[0]); fprintf(out,") then ");fprintf(out," \n"); uncompile(ast->son[1]);
				break;
			case ASTREE_ELSE:
                		fprintf(out,"if("); uncompile(ast->son[0]); fprintf(out,") then "); uncompile(ast->son[1]);fprintf(out,"else "); uncompile(ast->son[1]);
				break;  
			case ASTREE_ARRINI:
                		fprintf(out,"%s", ast->symbol->text); fprintf(out,": "); uncompile(ast->son[0]); fprintf(out,"["); 	uncompile(ast->son[1]); fprintf(out,"]"); 	
				
				if(ast->son[2]!=NULL)
					uncompile(ast->son[2]);
				fprintf(out,";");
                		break;
			default:
				printf("ERRO\n");
				break;
		}
	}
 
	return;

}


int main(int argc, char *argv[]){
    
	int fecha;
			
	if(argc<3){
		fprintf(stderr,"Execute: ./etapa5 nomearquivo.lang nomearquivo2.lang\n");
		return 1;
	}
	if(!(yyin = fopen(argv[1],"r"))){
		fprintf(stderr,"Nao foi possivel abrir o arquivo %s.\n",argv[1]);
		return 2;
	}
	
	initMe();
	
	yyparse();

	ASTREE *ast = getAst();

    	out = fopen(argv[2], "w");

    	if(out == NULL){
        	fprintf(stderr,"Nao eh possivel abrir o arquivo %s.\n",argv[2]);
		return 2;
		}else{
		 uncompile(ast);
}
	    
	if((fecha = fclose(out)) != 0)
		fprintf(stderr,"Erro ao fechar o arquivo %s.\n",argv[2]);

	fprintf(stderr,"\n");
	hashPrint();

	resultSemantic();    	

    return 0; 
}
