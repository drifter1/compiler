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

/* Available options for compiler stage selection
 * 0 - do nothing
 * 1 - only lexical analysis
 * 2 - lexical + syntax
 * 3 - lexical + syntax + semantic
 * 4 - lexical + syntax + semantic + IR
 * 5 - full pipeline
 */

#ifndef COMPILER_STAGE
#define COMPILER_STAGE 5
#endif

/* ----------------------DEBUG RELATED---------------------- */

#if DEBUG

#include "debug.h"

#endif

/* ----------------------ERROR RELATED---------------------- */

#if !STOP_ON_ERROR

#ifndef ALLOWED_ERRORS
#define ALLOWED_ERRORS 5
#endif

#endif

/* -----------------COMPILER STAGES RELATED----------------- */

#if COMPILER_STAGE >= 1
#define ENABLE_LEX 1
#else
#define ENABLE_LEX 0
#endif

#if COMPILER_STAGE >= 2
#define ENABLE_SYNTAX 1
#else
#define ENABLE_SYNTAX 0
#endif

#if COMPILER_STAGE >= 3
#define ENABLE_SEMANTIC 1
#else
#define ENABLE_SEMANTIC 0
#endif

#if COMPILER_STAGE >= 4
#define ENABLE_IR 1
#else
#define ENABLE_IR 0
#endif

/* ----------------FLEX / BISON REQUIREMENTS---------------- */

extern FILE *yyin;
extern FILE *yyout;

extern int yylineno;

int yylex();
int yyparse();
void yyerror(const char *s);

#endif /* COMPILER_H */