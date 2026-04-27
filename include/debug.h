#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

/* -------------------MAIN DEBUG SETTINGS------------------- */

#ifndef LEX_DEBUG
#define LEX_DEBUG 1
#endif

#ifndef SYMTAB_DEBUG
#define SYMTAB_DEBUG 1
#endif

#ifndef AST_DEBUG
#define AST_DEBUG 1
#endif

#ifndef SCOPE_DEBUG
#define SCOPE_DEBUG 1
#endif

#ifndef CONTEXT_DEBUG
#define CONTEXT_DEBUG 1
#endif

#ifndef SEM_DEBUG
#define SEM_DEBUG 1
#endif

/* -------------LEXICAL ANALYSIS DEBUG SETTINGS------------- */

#if LEX_DEBUG

#ifndef LEX_DEBUG_COMMENTS
#define LEX_DEBUG_COMMENTS 0
#endif

#ifndef LEX_DEBUG_TOKENS
#define LEX_DEBUG_TOKENS 0
#endif

#ifndef LEX_DUMP_FILE_OUTPUT
#define LEX_DUMP_FILE_OUTPUT 1
#endif

#endif /* LEX_DEBUG */

#if LEX_DUMP_FILE_OUTPUT

extern FILE *lexer_dump_file;

#ifndef LEXER_DUMP_FILE_NAME
#define LEXER_DUMP_FILE_NAME "lexer_dump.out"
#endif

#endif /* LEX_DUMP_FILE_OUTPUT */

/* ---------------SYMBOL TABLE DEBUG SETTINGS--------------- */

#if SYMTAB_DEBUG

#ifndef SYMTAB_DEBUG_INSERT
#define SYMTAB_DEBUG_INSERT 1
#endif

#ifndef SYMTAB_DUMP_FILE_OUTPUT
#define SYMTAB_DUMP_FILE_OUTPUT 1
#endif

#endif /* SYMTAB_DEBUG */

#if SYMTAB_DUMP_FILE_OUTPUT

#ifndef SYMTAB_DUMP_FILE_NAME
#define SYMTAB_DUMP_FILE_NAME "symtab_dump.out"
#endif

#endif /* SYMTAB_DUMP_FILE_OUTPUT */

/* -----------ABSTRACT SYNTAX TREE DEBUG SETTINGS----------- */

#if AST_DEBUG

#ifndef AST_DEBUG_CREATE_NODE
#define AST_DEBUG_CREATE_NODE 1
#endif

#ifndef AST_DUMP_FILE_OUTPUT
#define AST_DUMP_FILE_OUTPUT 1
#endif

#endif /* AST_DEBUG */

#if AST_DUMP_FILE_OUTPUT

#ifndef AST_JSON_DUMP_FILE_NAME
#define AST_JSON_DUMP_FILE_NAME "ast.json"
#endif

#endif /* AST_DUMP_FILE_OUTPUT */

#endif /* DEBUG_H */