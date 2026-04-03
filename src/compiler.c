#include "../include/compiler.h"
#include <stdio.h>

const char *filename;

#if DEBUG
FILE *lexer_dump_file;
#endif

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

#if DEBUG
        // open lexer dump file
        lexer_dump_file = fopen(LEXER_DUMP_FILE_NAME, "w");
#endif

        // parsing
        yyparse();
        fclose(yyin);

#if DEBUG
        // close lexer dump file
        fclose(lexer_dump_file);

        printf("Parsing finished!\n");
#endif
        // semantic analysis
        semantic_analysis(ast);

#if DEBUG
        // symbol table dump
        printf("Dumping symbol table to file...\n");
        FILE *symtab_dump_file;
        symtab_dump_file = fopen(SYMTAB_DUMP_FILE_NAME, "w");
        dump_symbol_table(symtab_dump_file);
        fclose(symtab_dump_file);

        // abstract syntax tree json dump file
        printf("Dumping abstract syntax tree to JSON file...\n");
        json_dump_abstract_syntax_tree(AST_JSON_DUMP_FILE_NAME);
#endif

        exit(EXIT_SUCCESS);
    }

    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
}