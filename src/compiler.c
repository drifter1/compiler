#include "../include/compiler.h"
#include <stdio.h>

const char *filename;

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

        // open lexer dump file
        if (DEBUG)
            yyout = fopen(LEXER_DUMP_FILE_NAME, "w");

        // parsing
        yyparse();
        fclose(yyin);

        // close lexer dump file
        if (DEBUG)
            fclose(yyout);

        if (DEBUG)
            printf("Parsing finished!\n");

        // semantic analysis
        semantic_analysis(ast);

        // symbol table dump
        if (DEBUG) {
            printf("Dumping symbol table to file...\n");
            yyout = fopen(SYMTAB_DUMP_FILE_NAME, "w");
            dump_symbol_table(yyout);
            fclose(yyout);
        }

        // abstract syntax tree json dump file
        if (DEBUG) {
            printf("Dumping abstract syntax tree to JSON file...\n");
            json_dump_abstract_syntax_tree(AST_JSON_DUMP_FILE_NAME);
        }

        exit(EXIT_SUCCESS);
    }

    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
}