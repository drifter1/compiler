#ifndef COMPILER_H
#define COMPILER_H

#include "../include/ast.h"
#include "../include/json.h"
#include "../include/list.h"
#include "../include/scope.h"
#include "../include/semantics.h"
#include "../include/symtab.h"
#include "../include/types.h"

/* ------------------COMPILER SETTINGS----------------------- */
#define DEBUG 1

/* --------------FLEX / BISON REQUIREMENTS------------------- */

extern FILE *yyin;
extern FILE *yyout;

extern int yylineno;

int yylex();
int yyparse();
void yyerror();

#endif /* COMPILER_H */