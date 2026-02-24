#include "../include/semantics.h"
#include "../include/symtab.h"
#include <stdio.h>

extern FILE *yyin;
extern FILE *yyout;
extern int lineno;

int yylex();
int yyparse();

int main(int argc, char *argv[]) {

    // initialize symbol table
    init_hash_table();

    // parsing
    int flag;
    yyin = fopen(argv[1], "r");
    flag = yyparse();
    fclose(yyin);

    printf("Parsing finished!\n");

    /* remove print from revisit queue */
    revisit_queue *q = search_prev_queue("print");
    if (q == NULL) {         /* special case: first entry */
        if (queue != NULL) { /* check if queue not empty */
            queue = queue->next;
        }
    } else {
        q->next = q->next->next;
    }

    /* perform the remaining checks (assignments) */
    if (queue != NULL) {
        revisit_queue *cur;
        cur = queue;
        while (cur != NULL) {
            if (cur->revisit_type == ASSIGN_CHECK) {
                revisit(cur->st_name);
            }
            cur = cur->next;
        }
    }

    /* if still not empty -> Warning */
    if (queue != NULL) {
        printf(
            "Warning: Something has not been checked in the revisit queue!\n");
    }

    /* declare function type of "print" */
    func_declare("print", VOID_TYPE, 1, NULL);

    // symbol table dump
    yyout = fopen("symtab_dump.out", "w");
    symtab_dump(yyout);
    fclose(yyout);

    // revisit queue dump
    yyout = fopen("revisit_dump.out", "w");
    revisit_dump(yyout);
    fclose(yyout);

    return flag;
}
