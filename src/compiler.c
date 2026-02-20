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

    // initialize revisit queue
	queue = NULL;

    // parsing
    int flag;
    yyin = fopen(argv[1], "r");
    flag = yyparse();
    fclose(yyin);

    printf("Parsing finished!\n");
	
	if(queue != NULL){
		printf("Warning: Something has not been checked in the revisit queue!\n");
	}

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
