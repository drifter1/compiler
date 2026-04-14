#include "../include/compiler.h"

extern const char *filename; // defined in compiler.c

void internal_error(const char *error) {
    perror(error);
    exit(EXIT_FAILURE);
}

void lexical_analysis_error(const char *error, ...) {
    va_list args;
    va_start(args, error);

    fprintf(stderr, BWHT "%s:%d: " BRED "error: " CRESET, filename, yylineno);
    vfprintf(stderr, error, args);

    char line[256];
    int count = 0;
    FILE *fp;

    if (!(fp = fopen(filename, "r")))
        internal_error(filename);

    while (fgets(line, sizeof(line), fp) != NULL) {
        count++;
        if (count == yylineno) {
            fprintf(stderr, "\n    %4d | %s", yylineno, line);
        }
    }

    if (fclose(fp))
        internal_error(filename);

    fprintf(stderr, "         |");
    fprintf(stderr, " \n");

    va_end(args);

    exit(EXIT_FAILURE);
}
