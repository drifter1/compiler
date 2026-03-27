#ifndef JSON_H
#define JSON_H

#include "ast.h"
#include <jansson.h>

json_t *json_construct_ast_node(ast_node *node);
json_t *json_construct_ast_node_list(list_node *list_head);
json_t *json_construct_names(list_node *names);
json_t *json_construct_symtab_entry(symtab_entry *entry);
json_t *json_construct_scope(scope *scope);
json_t *json_construct_lines(list_node *lines);
json_t *json_construct_parameters(list_node *parameters);

#endif /* JSON_H */