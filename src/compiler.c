#include "../include/compiler.h"
#include <stdio.h>
#include <stdlib.h>

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

        /* declare function type of "print" */
        insert("print", 5, UNDEF, -1);
        func_declare("print", VOID_TYPE, 1, NULL);

        // parsing
        yyparse();
        fclose(yyin);

        if (DEBUG)
            printf("Parsing finished!\n");

        // AST traversal
        if (DEBUG)
            ast_traversal(ast);

        // symbol table dump
        if (DEBUG) {
            yyout = fopen("symtab_dump.out", "w");
            symtab_dump(yyout);
            fclose(yyout);
        }

        exit(EXIT_SUCCESS);
    }

    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
}
