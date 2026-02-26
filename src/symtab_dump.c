#include "../include/semantics.h"
#include "../include/symtab.h"
#include <stdio.h>

void symtab_dump(FILE *of) { /* dump file */
    int i;
    fprintf(of, "------------ -------------- ------ ------------\n");
    fprintf(of, "Name         Type           Scope  Line Numbers\n");
    fprintf(of, "------------ -------------- ------ ------------\n");
    for (i = 0; i < SIZE; ++i) {
        if (hash_table[i] != NULL) {
            list_t *l = hash_table[i];
            while (l != NULL) {
                RefList *t = l->lines;
                fprintf(of, "%-13s", l->st_name);
                if (l->st_type == INT_TYPE)
                    fprintf(of, "%-15s", "int");
                else if (l->st_type == REAL_TYPE)
                    fprintf(of, "%-15s", "real");
                else if (l->st_type == CHAR_TYPE)
                    fprintf(of, "%-15s", "char");
                else if (l->st_type == VOID_TYPE)
                    fprintf(of, "%-15s", "void");
                else if (l->st_type == ARRAY_TYPE) {
                    fprintf(of, "array of ");
                    if (l->inf_type == INT_TYPE)
                        fprintf(of, "%-6s", "int");
                    else if (l->inf_type == REAL_TYPE)
                        fprintf(of, "%-6s", "real");
                    else if (l->inf_type == CHAR_TYPE)
                        fprintf(of, "%-6s", "char");
                    else
                        fprintf(of, "%-13s", "undef");
                } else if (l->st_type == POINTER_TYPE) {
                    fprintf(of, "pointer to ");
                    if (l->inf_type == INT_TYPE)
                        fprintf(of, "%-4s", "int");
                    else if (l->inf_type == REAL_TYPE)
                        fprintf(of, "%-4s", "real");
                    else if (l->inf_type == CHAR_TYPE)
                        fprintf(of, "%-4s", "char");
                    else if (l->inf_type == VOID_TYPE)
                        fprintf(of, "%-4s", "void");
                    else
                        fprintf(of, "%-4s", "undef");
                } else if (l->st_type == FUNCTION_TYPE) {
                    fprintf(of, "func ret ");
                    if (l->inf_type == INT_TYPE)
                        fprintf(of, "%-6s", "int");
                    else if (l->inf_type == REAL_TYPE)
                        fprintf(of, "%-6s", "real");
                    else if (l->inf_type == CHAR_TYPE)
                        fprintf(of, "%-6s", "char");
                    else if (l->inf_type == VOID_TYPE)
                        fprintf(of, "%-6s", "void");
                    else
                        fprintf(of, "%-4s", "undef");
                } else
                    fprintf(of, "%-15s", "undef"); // if UNDEF or 0
                fprintf(of, "  %d  ", l->scope);
                while (t != NULL) {
                    fprintf(of, "%4d ", t->lineno);
                    t = t->next;
                }
                fprintf(of, "\n");
                l = l->next;
            }
        }
    }
}