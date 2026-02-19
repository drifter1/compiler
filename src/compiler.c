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
