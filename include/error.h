#ifndef ERROR_H
#define ERROR_H

/* -----------------------ERROR KINDS----------------------- */

typedef enum { ERROR, WARNING, NOTE } error_kind;

/* -----------------LEXICAL ANALYSIS ERRORS----------------- */

#define EOF_IN_COMMENT "EOF in comment"
#define UNRECOGNIZED_CHARACTER "Unrecognized character \'%c\' (ASCII value: %d)"

void internal_error(const char *error);
void lexical_analysis_error(const char *error, ...);

#endif /* ERROR_H */