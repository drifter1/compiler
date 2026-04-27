#include "../include/compiler.h"
#include <stdlib.h>

extern const char *filename; // defined in compiler.c

extern char *yytext; // defined in lex/yacc
extern int yyleng;   // defined in lex/yacc

#if !STOP_ON_ERROR

/* -----------------------ERROR COUNT----------------------- */

int error_count = 0;

#endif

/* ----------------ERROR REPORTING FUNCTIONS---------------- */

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

    // open file
    if (!(fp = fopen(filename, "r")))
        internal_error(filename);

    while (fgets(line, sizeof(line), fp) != NULL) {
        count++;
        // when in line of token
        if (count == yylineno) {
            fprintf(stderr, "\n    %4d | ", yylineno);
            print_colored_line(line, yytext, yyleng);
        }
    }

    // close file
    if (fclose(fp))
        internal_error(filename);

    fprintf(stderr, "         |");
    fprintf(stderr, " \n");

    va_end(args);

#if !STOP_ON_ERROR
    if (++error_count <= ALLOWED_ERRORS)
        return;
#endif

    exit(EXIT_FAILURE);
}

void syntax_analysis_error(int lineno, const char *error, ...) {
    va_list args;
    va_start(args, error);

    fprintf(stderr, BWHT "%s:%d: " BRED "error: " CRESET, filename, lineno);
    vfprintf(stderr, error, args);

    char line[256];
    int count = 0;
    FILE *fp;

    // open file
    if (!(fp = fopen(filename, "r")))
        internal_error(filename);

    while (fgets(line, sizeof(line), fp) != NULL) {
        count++;
        // when in line of token
        if (count == lineno) {
            fprintf(stderr, "\n    %4d | %s", lineno, line);
        }
    }

    // close file
    if (fclose(fp))
        internal_error(filename);

    fprintf(stderr, "         |");
    fprintf(stderr, " \n");

    va_end(args);

#if !STOP_ON_ERROR
    if (++error_count <= ALLOWED_ERRORS)
        return;
#endif

    exit(EXIT_FAILURE);
}

void semantic_analysis_error(int lineno, const char *error, ...) {
    va_list args;
    va_start(args, error);

    fprintf(stderr, BWHT "%s:%d: " BMAG "warning: " CRESET, filename, lineno);
    vfprintf(stderr, error, args);

    char line[256];
    int count = 0;
    FILE *fp;

    // open file
    if (!(fp = fopen(filename, "r")))
        internal_error(filename);

    while (fgets(line, sizeof(line), fp) != NULL) {
        count++;
        // when in line of token
        if (count == lineno) {
            fprintf(stderr, "\n    %4d | %s", lineno, line);
        }
    }

    // close file
    if (fclose(fp))
        internal_error(filename);

    fprintf(stderr, "         |");
    fprintf(stderr, " \n");

    va_end(args);

#if !STOP_ON_ERROR
    if (++error_count <= ALLOWED_ERRORS)
        return;
#endif

    exit(EXIT_FAILURE);
}

/* ---------------------HELPER FUNCTIONS-------------------- */

int find_token_start_col(const char *line, const char *token) {
    const char *p = line;
    int col = 0;

    while (*p) {
        /* token column found */
        if (*p == token[0])
            return col;
        ++p;
        ++col;
    }

    /* token not found */
    return -1;
}

void print_colored_line(const char *line, const char *token, int len) {
    int start_col = find_token_start_col(line, token);

    // when not found simply print out the line
    if (start_col < 0) {
        fprintf(stderr, "%s\n", line);
        return;
    }

    // print text before the token
    fwrite(line, 1, start_col, stderr);

    // print token in bold underlined red
    fprintf(stderr, URED BRED "%.*s" CRESET, len, token);

    // print remainder line text
    fputs(line + start_col + len, stderr);
}