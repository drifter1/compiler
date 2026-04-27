#include "../include/compiler.h"

const char *filename;

#if LEX_DUMP_FILE_OUTPUT
FILE *lexer_dump_file;
#endif

int main(int argc, char *argv[]) {

    if (argc == 2) {
        filename = argv[1];

        // open input file
        if (!(yyin = fopen(filename, "r")))
            internal_error(filename);

#if ENABLE_SYNTAX

        // initialize symbol table
        init_symbol_table();

        // initialize scope
        init_scope();
#endif

#if ENABLE_LEX && LEX_DUMP_FILE_OUTPUT
        // open lexer dump file
        if (!(lexer_dump_file = fopen(LEXER_DUMP_FILE_NAME, "w")))
            internal_error(LEXER_DUMP_FILE_NAME);
#endif

#if ENABLE_SYNTAX
        yyparse();
#elif ENABLE_LEX
        while (yylex())
            ;
#endif

        // close input file
        if (fclose(yyin))
            internal_error(filename);

#if ENABLE_LEX && LEX_DUMP_FILE_OUTPUT
        // close lexer dump file
        if (fclose(lexer_dump_file))
            internal_error(LEXER_DUMP_FILE_NAME);
#endif

#if ENABLE_SEMANTIC
        semantic_analysis(ast);
#endif

#if ENABLE_IR
        intermediate_code_generation(ast);
#endif

#if ENABLE_SYNTAX && SYMTAB_DUMP_FILE_OUTPUT
        printf("Dumping symbol table to file...\n");
        FILE *symtab_dump_file;
        if (!(symtab_dump_file = fopen(SYMTAB_DUMP_FILE_NAME, "w")))
            internal_error(SYMTAB_DUMP_FILE_NAME);
        dump_symbol_table(symtab_dump_file);
        if (fclose(symtab_dump_file))
            internal_error(SYMTAB_DUMP_FILE_NAME);
#endif

#if ENABLE_SYNTAX && AST_DUMP_FILE_OUTPUT
        printf("Dumping abstract syntax tree to JSON file...\n");
        json_dump_abstract_syntax_tree(AST_JSON_DUMP_FILE_NAME);

#endif

#if ENABLE_IR

        // open output file
        if (!(yyout = fopen(OUTPUT_FILE_NAME, "w")))
            internal_error(OUTPUT_FILE_NAME);

        // output intermediate code
        tac_list_print(yyout);

        // close output file
        if (fclose(yyout))
            internal_error(OUTPUT_FILE_NAME);
#endif

        // memory free-up

#if ENABLE_IR
        tac_list_free();
#endif

#if ENABLE_SYNTAX
        free_ast_node(ast);
        free_symbol_table();
#endif

        exit(EXIT_SUCCESS);
    }

    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
}