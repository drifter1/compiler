#ifndef COMPILER_H
#define COMPILER_H

#include "../include/ast.h"
#include "../include/context.h"
#include "../include/ir.h"
#include "../include/json.h"
#include "../include/list.h"
#include "../include/scope.h"
#include "../include/semantics.h"
#include "../include/symtab.h"
#include "../include/tac.h"
#include "../include/types.h"

/* --------------------COMPILER SETTINGS-------------------- */

#ifndef OUTPUT_FILE_NAME
#define OUTPUT_FILE_NAME "compiler.out"
#endif

#ifndef DEBUG
#define DEBUG 1
#endif

/* ----------------------DEBUG RELATED---------------------- */

#if DEBUG
extern FILE *lexer_dump_file;

#ifndef LEXER_DUMP_FILE_NAME
#define LEXER_DUMP_FILE_NAME "lexer_dump.out"
#endif

#ifndef SYMTAB_DUMP_FILE_NAME
#define SYMTAB_DUMP_FILE_NAME "symtab_dump.out"
#endif

#ifndef AST_JSON_DUMP_FILE_NAME
#define AST_JSON_DUMP_FILE_NAME "ast.json"
#endif

#endif

/* ----------------FLEX / BISON REQUIREMENTS---------------- */

extern FILE *yyin;
extern FILE *yyout;

extern int yylineno;

int yylex();
int yyparse();
void yyerror();

#endif /* COMPILER_H */