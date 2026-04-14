#include "../include/compiler.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void internal_error(const char *error) {
    perror(error);
    exit(EXIT_FAILURE);
}

void lexical_analysis_error(const char *error, ...) {
    va_list args;
    va_start(args, error);

    fprintf(stderr, RED "Lexical error at line %d. " CRESET, yylineno);
    vfprintf(stderr, error, args);
    fprintf(stderr, " \n");

    va_end(args);

    exit(EXIT_FAILURE);
}
