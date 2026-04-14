#ifndef ERROR_H
#define ERROR_H

/* -----------------------ERROR KINDS----------------------- */

typedef enum { ERROR, WARNING, NOTE } error_kind;

/* -----------------LEXICAL ANALYSIS ERRORS----------------- */

#define EOF_IN_COMMENT "EOF in comment"
#define UNRECOGNIZED_CHARACTER "Unrecognized character \'%c\' (ASCII value: %d)"

/* ----------------ERROR REPORTING FUNCTIONS---------------- */

void internal_error(const char *error);
void lexical_analysis_error(const char *error, ...);

/* ---------------------HELPER FUNCTIONS-------------------- */

int find_token_start_col(const char *line, const char *token);
void print_colored_line(const char *line, const char *token, int len);

#endif /* ERROR_H */