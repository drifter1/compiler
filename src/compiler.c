#include "../include/compiler.h"

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

        // symbol table dump
        if (DEBUG) {
            yyout = fopen("symtab_dump.out", "w");
            dump_symbol_table(yyout);
            fclose(yyout);
        }

        // abstract syntax tree json dump file
        if (DEBUG) {
            json_dump_file(json_construct_ast_node(ast), "ast.json",
                           JSON_INDENT(4));
        }

        exit(EXIT_SUCCESS);
    }

    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
}