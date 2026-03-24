#ifndef SEMANTICS_H
#define SEMANTICS_H

#include "ast.h"
#include "types.h"

// Function Declarations

void semantic_analysis(ast_node *ast_node);
void semantic_analysis_list(list_node *list_head);

data_type get_result_type(data_type type_1, data_type type_2,
                          operator_type op_type);

void type_error(data_type type_1, data_type type_2, operator_type op_type);

data_type expression_data_type(ast_node *ast_node);

#endif /* SEMANTICS_H */