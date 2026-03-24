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
        init_symbol_table();

        // initialize scope
        init_scope();

        // parsing
        yyparse();
        fclose(yyin);

        if (DEBUG)
            printf("Parsing finished!\n");

        // semantic analysis
        semantic_analysis(ast);

        // AST traversal
        if (DEBUG)
            ast_traversal(ast);

        // symbol table dump
        if (DEBUG) {
            yyout = fopen("symtab_dump.out", "w");
            dump_symbol_table(yyout);
            fclose(yyout);
        }

        exit(EXIT_SUCCESS);
    }

    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
}
