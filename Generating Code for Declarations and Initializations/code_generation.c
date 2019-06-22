#include "code_generation.h"

void generate_code(){	
	FILE *fp;
	fp = fopen("out.s", "w");
	
	generate_data_declarations(fp);
	
	fclose(fp);
}

void generate_data_declarations(FILE *fp){
	/* print .data */
	fprintf(fp, ".data\n");	
	
	/* loop through the symbol table's lists */
	int i;
	for (i = 0; i < SIZE; i++){ 
		/* if hashtable list not empty */
		if (hash_table[i] != NULL){ 
			list_t *l = hash_table[i];
			/* loop through list */
			while (l != NULL){ 
				/* Simple Variables */
				if (l->st_type == INT_TYPE){
					fprintf(fp, "%s: .word %d\n", l->st_name, l->val.ival);
				}
				else if (l->st_type == REAL_TYPE){
					fprintf(fp, "%s: .double %f\n", l->st_name, l->val.fval);
				}
				else if (l->st_type == CHAR_TYPE){
					fprintf(fp, "%s: .byte \'%c\'\n", l->st_name, l->val.cval);
				}				
				
				/* Array */
				else if (l->st_type == ARRAY_TYPE){
					if (l->inf_type == INT_TYPE){
						fprintf(fp, "%s: .space %d\n", l->st_name, l->array_size*4);
					}
					else if (l->inf_type  == REAL_TYPE){
						fprintf(fp, "%s: .space %d\n", l->st_name, l->array_size*8);
					}
					else if (l->inf_type  == CHAR_TYPE){
						fprintf(fp, "%s: .space %d\n", l->st_name, l->array_size*1);
					}
				}
				
				/* Pointer */
				else if (l->st_type == POINTER_TYPE){
					fprintf(fp, "%s: .word 0\n", l->st_name);
				}
				
				/* Function (ignore) */
				else if (l->st_type == FUNCTION_TYPE){
					
				}
			
				l = l->next;
			}
		}
	}
}
