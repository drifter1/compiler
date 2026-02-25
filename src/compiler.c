#include "../include/revqueue.h"
#include "../include/semantics.h"
#include "../include/symtab.h"
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;
extern FILE *yyout;
extern int lineno;

int yylex();
int yyparse();

char *filename;

int main(int argc, char *argv[]) {

    if (argc == 2) {
        filename = argv[1];

        // open file
        if (!(yyin = fopen(filename, "r"))) {
            fprintf(stderr, "Unable to open file %s\n", filename);
            exit(EXIT_FAILURE);
        }

        // initialize symbol table
        init_hash_table();

        // parsing
        yyparse();
        fclose(yyin);

        printf("Parsing finished!\n");

        /* remove print from revisit queue */
        remove_print();

        /* perform the remaining checks (assignments) */
        perform_remaining_checks();

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

        exit(EXIT_SUCCESS);
    }
    
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
}
