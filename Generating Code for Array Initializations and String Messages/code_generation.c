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
	int i, j;
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
					/* not initialized */
					if(l->vals == NULL){
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
					/* initialized */
					else{
						if (l->inf_type == INT_TYPE){
							fprintf(fp, "%s: .word ", l->st_name);
							for(j = 0; j < l->array_size - 1; j++){
								fprintf(fp, "%d, ", l->vals[j].ival);
							}
							fprintf(fp, "%d\n", l->vals[l->array_size - 1].ival);
						}
						else if (l->inf_type  == REAL_TYPE){
							fprintf(fp, "%s: .double ", l->st_name);
							for(j = 0; j < l->array_size - 1; j++){
								fprintf(fp, "%f, ", l->vals[j].fval);
							}
							fprintf(fp, "%f\n", l->vals[l->array_size - 1].fval);
						}
						else if (l->inf_type  == CHAR_TYPE){
							fprintf(fp, "%s: .byte ", l->st_name);
							for(j = 0; j < l->array_size - 1; j++){
								fprintf(fp, "%c, ", l->vals[j].cval);
							}
							fprintf(fp, "%c\n", l->vals[l->array_size - 1].cval);
						}
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
	
	/* loop through the string messages */
	for(i = 0; i < num_of_msg; i++){
		fprintf(fp, "msg%d: .asciiz %s\n", (i + 1), str_messages[i]);
	}
}
