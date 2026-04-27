#ifndef COMPILER_H
#define COMPILER_H

#include "ansi_colors.h"
#include "ast.h"
#include "context.h"
#include "error.h"
#include "ir.h"
#include "json.h"
#include "list.h"
#include "scope.h"
#include "semantics.h"
#include "symtab.h"
#include "tac.h"
#include "types.h"

/* --------------------COMPILER SETTINGS-------------------- */

#ifndef OUTPUT_FILE_NAME
#define OUTPUT_FILE_NAME "compiler.ic"
#endif

#ifndef DEBUG
#define DEBUG 1
#endif

#ifndef STOP_ON_ERROR
#define STOP_ON_ERROR 0
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

/* ----------------------ERROR RELATED---------------------- */

#if !STOP_ON_ERROR

#ifndef ALLOWED_ERRORS
#define ALLOWED_ERRORS 5
#endif

#endif

/* ----------------FLEX / BISON REQUIREMENTS---------------- */

extern FILE *yyin;
extern FILE *yyout;

extern int yylineno;

int yylex();
int yyparse();
void yyerror(const char *s);

#endif /* COMPILER_H */