#ifndef COMPILER_H
#define COMPILER_H

#include "../include/ast.h"
#include "../include/json.h"
#include "../include/list.h"
#include "../include/scope.h"
#include "../include/semantics.h"
#include "../include/symtab.h"
#include "../include/types.h"

/* --------------------COMPILER SETTINGS-------------------- */

#define DEBUG 1

/* ----------------------DEBUG RELATED---------------------- */

#ifdef DEBUG
extern FILE *lexer_dump_file;
#define LEXER_DUMP_FILE_NAME "lexer_dump.out"
#define SYMTAB_DUMP_FILE_NAME "symtab_dump.out"
#define AST_JSON_DUMP_FILE_NAME "ast.json"
#endif

/* ----------------FLEX / BISON REQUIREMENTS---------------- */

extern FILE *yyin;
extern FILE *yyout;

extern int yylineno;

int yylex();
int yyparse();
void yyerror();

#endif /* COMPILER_H */