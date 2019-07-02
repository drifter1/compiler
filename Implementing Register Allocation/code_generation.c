#include "code_generation.h"

/* main assembly code generation function */
void generate_code(){	
	FILE *fp;
	fp = fopen("out.s", "w");
	
	generate_data_declarations(fp);
	
	generate_statements(fp);
	
	fclose(fp);
}

/* data declaration assembly code */
void generate_data_declarations(FILE *fp){
	/* print .data */
	fprintf(fp, ".data\n");	
	
	/* loop through the symbol table's lists */
	fprintf(fp, "# variables\n");
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
	fprintf(fp, "# messages\n");
	for(i = 0; i < num_of_msg; i++){
		fprintf(fp, "msg%d: .asciiz %s\n", (i + 1), str_messages[i]);
	}
}

/* statements assembly code */
void generate_statements(FILE *fp){
	
	/* print .text */
	fprintf(fp, "\n.text\n");
	
	/* Main Function Register Allocation */
	initGraph();
	
	main_reg_allocation(main_decl_tree);
	main_reg_allocation(main_func_tree);
	
	printVarArray();
	
	printGraph();
	
	/* Main Function Register Assignment */
	int i;
	int *colors = greedyColoring();
	
	printf("Colors:\n");
	for(i = 0; i < var_count; i++){
		printf("%s: %d\n", var_name[i], colors[i]);
	}
	
	// assign register-color value as reg_name
	list_t *l;
	for(i = 0; i < var_count; i++){
		l = lookup(var_name[i]);
		l->reg_name = colors[i];
	}
	
	/* print main: */
	fprintf(fp, "main:\n");
}

/* Graph Functions */
void initGraph(){
	g = (AdjGraph*) malloc(sizeof(AdjGraph));
	g->adj = NULL;
	g->vertexCount = 0;
}

void insertEdge(int i, int j){
	
	AdjList *l;
	
	// check if less than zero (constant in operation)
	if(i < 0 || j < 0){
		return;
	}
	
	/* find max */
	int max;
	if(i > j){
		max = i;
	}
	else{
		max = j;
	}

	/* variable count is max + 1 */
	max = max + 1;

	/* manage space */
	if (g->vertexCount == 0){ /* first allocation */
		g->adj = (AdjList**) malloc(max * sizeof(AdjList*));
		g->vertexCount = max;
	}
	else if(g->vertexCount < max){ /* allocate space for more variables */
		g->adj = (AdjList**) realloc(g->adj, max * sizeof(AdjList*));
		g->vertexCount = max;
	}
	
	/* insert edge i-j */
	l = g->adj[i];
	
	while ((l != NULL) && (l->index != j)) l = l->next;
	
	if (l == NULL){
		l = (AdjList*) malloc(sizeof(AdjList));
		l->index = j;
		l->next = g->adj[i];
		g->adj[i] = l;
	}
	
	/* insert edge j-i */
	l = g->adj[j];
	
	while ((l != NULL) && (l->index != i)) l = l->next;
	
	if (l == NULL){
		l = (AdjList*) malloc(sizeof(AdjList));
		l->index = i;
		l->next = g->adj[j];
		g->adj[j] = l;
	}
}

void printGraph(){	
	int i;
	AdjList *l;
	
	printf("AdjGraph:\n");
	for(i = 0 ; i < g->vertexCount; i++){
		printf("%d: ", i);
		l = g->adj[i];
		while(l != NULL){
			printf("%d ", l->index);
			l = l->next;
		}
		printf("\n");
	}
	printf("\n");
}

int *greedyColoring(){
	
	AdjList *l;
	int i;
	
	int V = g->vertexCount;
	
	// color array
	int *colors;
	colors = (int*) malloc(V * sizeof(int));

	// initialize all vertices to '-1', which means unassigned
	for(i = 0; i < V; i++){
		colors[i] = -1;
	}

	// assign first color (0) to first vertex
	colors[0] = 0;

	// boolean array that shows us which colors are still available
	int *available;
	available = (int*) malloc(V * sizeof(int));

	// starting off, all colors are available
	for(i = 0; i < V; i++){
		available[i] = 1;
	}

	// assign colors to the remaining V-1 vertices
	int u;
	for (u = 1; u < V; u++) {
		// process adjacent vertices and flag their colors as unavailable
		l = g->adj[u];
		while (l != NULL) {
			i = l->index;
			if (colors[i] != -1) {
				available[colors[i]] = 0;
			}
			l = l->next;
		}

		// find the first avaiable color
		int cr;
		for (cr = 0; cr < V; cr++) {
			if (available[cr] == 1){
				break;
			}
		}

		// assign the first avaiable color
		colors[u] = cr;

		// reset values back to true for the next iteration
		for(i = 0; i < V; i++){
			available[i] = 1;
		}
	}
	
	return colors;
}

/* Variable Array Functions */

void insertVar(char *name){
	/* first insertion */
	if(var_count == 0){
		var_name = (char**) malloc(1 * sizeof(char*));
		var_name[0] = (char*) malloc((strlen(name) + 1) * sizeof(char));		
		strcpy(var_name[0], name);
		
		var_count++;
	}
	else{
		/* check if variable already exists */
		int flag = 0;
		int i;
		for(i = 0; i < var_count; i++){
			if(strcmp(var_name[i], name) == 0){
				flag = 1;
				break;
			}
		}
		
		/* not inserted yet */
		if(flag == 0){
			var_name = (char**) realloc(var_name, (var_count + 1) * sizeof(char*));
			var_name[var_count] = (char*) malloc((strlen(name) + 1) * sizeof(char));		
			strcpy(var_name[var_count], name);
			
			var_count++;
		}
	}
}

int getVarIndex(char *name){
	int index = -1;
	
	int i;
	for(i = 0; i < var_count; i++){
		if(strcmp(var_name[i], name) == 0){
			index = i;
			break;
		}
	}
	
	return index;
}

void printVarArray(){
	int i;
	printf("VarArray:\n");
	for(i = 0 ; i < var_count; i++){
		printf("%d: %s\n", i, var_name[i]);
	}
	printf("\n");
}

void main_reg_allocation(AST_Node *node){
	static int inst_num = 0;
	
	AST_Node_Declarations *temp_declarations;
	AST_Node_Decl *temp_decl;
	AST_Node_Arithm *temp_arithm;
	AST_Node_Bool *temp_bool;
	AST_Node_Rel *temp_rel;
	AST_Node_Equ *temp_equ;
	AST_Node_Statements *temp_statements;
	AST_Node_If *temp_if;
	AST_Node_Elsif *temp_elsif;
	AST_Node_For *temp_for;
	AST_Node_While *temp_while;
	AST_Node_Incr *temp_incr;
	AST_Node_Assign *temp_assign;
	AST_Node_Func_Call *temp_func_call;
	AST_Node_Call_Params *temp_call_params;
	
	/* temp variable name */
	char name[MAXTOKENLEN];
	
	int i;
	
	/* check if empty */
	if(node == NULL){
		return;
	}
	
	switch(node->type){
		/* declarations case */
		case DECLARATIONS:
			temp_declarations = (struct AST_Node_Declarations *) node;	
			for(i = 0; i < temp_declarations->declaration_count; i++){
				main_reg_allocation(temp_declarations->declarations[i]);
			}
			break;
		/* declaration case */
		case DECL_NODE:
			temp_decl = (struct AST_Node_Decl *) node;
			for(i = 0; i < temp_decl->names_count; i++){
				insertVar(temp_decl->names[i]->st_name);
				
				/* graph index */
				temp_decl->names[i]->g_index = getVarIndex(temp_decl->names[i]->st_name);
			}
			break;
		/* left and right child cases */
		case BASIC_NODE:
			main_reg_allocation(node->left);
			main_reg_allocation(node->right);
			break;
		case ARITHM_NODE:
			temp_arithm = (struct AST_Node_Arithm *) node;
			
			main_reg_allocation(node->left);
			main_reg_allocation(node->right);
		
			/* insert temporary */
			sprintf(name, "_temp%d", temp_count);
			insertVar(name);
			temp_count++;
			
			printf("Inserting %s for node:\n", name);
			ast_print_node(node);
			printf("\n");
			
			declare = 1;
			insert(name, strlen(name), temp_arithm->data_type, -1);
			declare = 0;
			
			/* graph index */
			temp_arithm->g_index = var_count - 1;
			
			/* manage graph */
			if(temp_arithm->op != INC && temp_arithm->op != DEC){
				insertEdge(temp_arithm->g_index, getGraphIndex(temp_arithm->left));
				insertEdge(temp_arithm->g_index, getGraphIndex(temp_arithm->right));
				insertEdge(getGraphIndex(temp_arithm->left), getGraphIndex(temp_arithm->right));
			}
			else{
				insertEdge(temp_arithm->g_index, getGraphIndex(temp_arithm->left));
			}
			
			inst_num++;
			break;
		case BOOL_NODE:
			temp_bool = (struct AST_Node_Bool *) node;
			
			main_reg_allocation(node->left);
			main_reg_allocation(node->right);
		
			/* insert temporary */
			sprintf(name, "_temp%d", temp_count);
			insertVar(name);
			temp_count++;
			
			printf("Inserting %s for node:\n", name);
			ast_print_node(node);
			printf("\n");
			
			declare = 1;
			insert(name, strlen(name), temp_bool->data_type, -1);
			declare = 0;
			
			/* graph index */
			temp_bool->g_index = var_count - 1;
			
			/* manage graph */
			if(temp_bool->op != NOT){
				insertEdge(temp_bool->g_index, getGraphIndex(temp_bool->left));
				insertEdge(temp_bool->g_index, getGraphIndex(temp_bool->right));	
				insertEdge(getGraphIndex(temp_bool->left), getGraphIndex(temp_bool->right));
			}
			else{
				insertEdge(temp_bool->g_index, getGraphIndex(temp_bool->left));
			}
			
			inst_num++;
			break;
		case REL_NODE:
			temp_rel = (struct AST_Node_Rel *) node;
			
			main_reg_allocation(node->left);
			main_reg_allocation(node->right);
		
			/* insert temporary */
			sprintf(name, "_temp%d", temp_count);
			insertVar(name);
			temp_count++;
			
			printf("Inserting %s for node:\n", name);
			ast_print_node(node);
			printf("\n");
			
			declare = 1;
			insert(name, strlen(name), temp_rel->data_type, -1);
			declare = 0;
			
			/* graph index */
			temp_rel->g_index = var_count - 1;
			
			/* manage graph */
			insertEdge(temp_rel->g_index, getGraphIndex(temp_rel->left));
			insertEdge(temp_rel->g_index, getGraphIndex(temp_rel->right));	
			insertEdge(getGraphIndex(temp_rel->left), getGraphIndex(temp_rel->right));
			
			inst_num++;
			break;
		case EQU_NODE:
			temp_equ = (struct AST_Node_Equ *) node;
			
			main_reg_allocation(node->left);
			main_reg_allocation(node->right);
		
			/* insert temporary */
			sprintf(name, "_temp%d", temp_count);
			insertVar(name);
			temp_count++;
			
			printf("Inserting %s for node:\n", name);
			ast_print_node(node);
			printf("\n");
			
			declare = 1;
			insert(name, strlen(name), temp_equ->data_type, -1);
			declare = 0;
			
			/* graph index */
			temp_equ->g_index = var_count - 1;
			
			/* manage graph */
			insertEdge(temp_equ->g_index, getGraphIndex(temp_equ->left));
			insertEdge(temp_equ->g_index, getGraphIndex(temp_equ->right));	
			insertEdge(getGraphIndex(temp_equ->left), getGraphIndex(temp_equ->right));
			
			inst_num++;
			break;
		/* reference case */
		case REF_NODE:
			/* all the entries are already being managed by the Decl case */
			break;
		/* constant case */
		case CONST_NODE:
			/* already managed in getGraphIndex */
			break;
		/* statements case */
		case STATEMENTS:
			temp_statements = (struct AST_Node_Statements *) node;	
			for(i = 0; i < temp_statements->statement_count; i++){
				main_reg_allocation(temp_statements->statements[i]);
			}
			break;
		/* the if case */
		case IF_NODE:
			temp_if = (struct AST_Node_If *) node;
		
			main_reg_allocation(temp_if->condition);
			inst_num++;
		
			main_reg_allocation(temp_if->if_branch);
		
			if(temp_if->elseif_count > 0 ){
				for(i = 0; i < temp_if->elseif_count; i++){
					main_reg_allocation(temp_if->elsif_branches[i]);
				}	
			}
	
			if(temp_if->else_branch != NULL){
				main_reg_allocation(temp_if->else_branch);
			}
			break;
		/* the else if case */
		case ELSIF_NODE:
			temp_elsif = (struct AST_Node_Elsif *) node;
			
			main_reg_allocation(temp_elsif->condition);
			inst_num++;
			
			main_reg_allocation(temp_elsif->elsif_branch);
			break;
		/* for case */
		case FOR_NODE:
			temp_for = (struct AST_Node_For *) node;
			
			//main_reg_allocation(temp_for->initialize);
			inst_num++;
			
			//main_reg_allocation(temp_for->condition);
			inst_num++;
			
			main_reg_allocation(temp_for->for_branch);
			
			//main_reg_allocation(temp_for->increment);
			inst_num++;
			break;
		/* while case */
		case WHILE_NODE:
			temp_while = (struct AST_Node_While *) node;
			main_reg_allocation(temp_while->condition);
			inst_num++;
			
			main_reg_allocation(temp_while->while_branch);
			break;
		/* assign case */
		case ASSIGN_NODE:
			temp_assign = (struct AST_Node_Assign *) node;
			
			/* manage graph */
			insertEdge(temp_assign->entry->g_index, getGraphIndex(temp_assign->assign_val));
			
			main_reg_allocation(temp_assign->assign_val);
			break;
		/* simple case */
		case SIMPLE_NODE:
			inst_num++;
			break;
		/* increment statement */
		case INCR_NODE:
			temp_incr = (AST_Node_Incr*) node;
			
			inst_num++;
			break;
		/* function call case */
		case FUNC_CALL:
			temp_func_call = (struct AST_Node_Func_Call *) node;
			if(temp_func_call->num_of_pars != 0){
				for(i = 0; i < temp_func_call->num_of_pars; i++){
					main_reg_allocation(temp_func_call->params[i]);
				}
			}
			
			/* insert temporary when function non-void */
			if(temp_func_call->entry->inf_type != VOID_TYPE){
				sprintf(name, "_temp%d", temp_count);
				insertVar(name);
				temp_count++;
				
				printf("Inserting %s for node:\n", name);
				ast_print_node(node);
				printf("\n");
				
				declare = 1;
				insert(name, strlen(name), temp_func_call->entry->inf_type, -1);
				declare = 0;
				
				/* graph index */
				temp_func_call->g_index = var_count - 1;
			}			
			
			inst_num++;
			break;
		case CALL_PARAMS:
			temp_call_params = (struct AST_Node_Call_Params*) node;
			if(temp_call_params->num_of_pars > 0){
				for(i = 0; i < temp_call_params->num_of_pars; i++){
					main_reg_allocation(temp_call_params->params[i]);
				}
			}
			break;
		/* function declaration stuff */
		case FUNC_DECLS:
		case FUNC_DECL:
		case RET_TYPE:
		case DECL_PARAMS:
		case RETURN_NODE:
			/* can't occur in main */
			break;
		default: /* wrong choice case */
			fprintf(stderr, "Error in node selection!\n");
			exit(1);
	}
}
