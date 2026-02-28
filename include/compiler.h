#include "../include/ast.h"
#include "../include/revqueue.h"
#include "../include/semantics.h"
#include "../include/symtab.h"

#ifndef COMPILER_H
#define COMPILER_H

/* ------------------COMPILER SETTINGS----------------------- */
#define DEBUG 1

/* --------------FLEX / BISON REQUIREMENTS------------------- */

extern FILE *yyin;
extern FILE *yyout;

int yyparse();

#endif /* COMPILER_H */