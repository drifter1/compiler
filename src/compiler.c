#include "../include/compiler.h"
#include <stdio.h>
#include <stdlib.h>

const char *filename;

#if DEBUG
FILE *lexer_dump_file;
#endif

int main(int argc, char *argv[]) {

    if (argc == 2) {
        filename = argv[1];

        // open input file
        if (!(yyin = fopen(filename, "r")))
            internal_error(filename);

        // initialize symbol table
        init_symbol_table();

        // initialize scope
        init_scope();

#if DEBUG
        // open lexer dump file
        if (!(lexer_dump_file = fopen(LEXER_DUMP_FILE_NAME, "w")))
            internal_error(LEXER_DUMP_FILE_NAME);
#endif

        // perform parsing
        yyparse();

        // close input file
        if (fclose(yyin))
            internal_error(filename);

#if DEBUG
        // close lexer dump file
        if (fclose(lexer_dump_file))
            internal_error(LEXER_DUMP_FILE_NAME);
#endif

        // perform semantic analysis
        semantic_analysis(ast);

        // perform intermediate code generation
        intermediate_code_generation(ast);

#if DEBUG
        // symbol table dump
        printf("Dumping symbol table to file...\n");
        FILE *symtab_dump_file;
        if (!(symtab_dump_file = fopen(SYMTAB_DUMP_FILE_NAME, "w")))
            internal_error(SYMTAB_DUMP_FILE_NAME);
        dump_symbol_table(symtab_dump_file);
        if (fclose(symtab_dump_file))
            internal_error(SYMTAB_DUMP_FILE_NAME);

        // abstract syntax tree json dump file
        printf("Dumping abstract syntax tree to JSON file...\n");
        json_dump_abstract_syntax_tree(AST_JSON_DUMP_FILE_NAME);
#endif

        // open output file
        if (!(yyout = fopen(OUTPUT_FILE_NAME, "w")))
            internal_error(OUTPUT_FILE_NAME);

        // output intermediate code
        tac_list_print(yyout);

        // close output file
        if (fclose(yyout))
            internal_error(OUTPUT_FILE_NAME);

        // memory free-up
        tac_list_free();
        free_ast_node(ast);
        free_symbol_table();

        exit(EXIT_SUCCESS);
    }

    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
}