%{
	#include "../include/compiler.h"
	#include "../build/parser.tab.h"

	char *to_id(char *str_in, int len);
	char to_char(char *str);
	char *to_string(char *str_in, int len);
%}

%option yylineno noyywrap noinput nounput never-interactive

%x ML_COMMENT

alpha 				[a-zA-Z]
digit 				[0-9]
nzdigit				[1-9]
alnum 				{alpha}|{digit}
print				[ -~]

ID 					{alpha}{alnum}*
ICONST				"0"|{nzdigit}{digit}*
FCONST				(("0"|{nzdigit}{digit}*)?"."{digit}+)|({nzdigit}{digit}*".")
CCONST				(\'{print}\')|(\'\\[nftrbv]\')
STRING				\"{print}*\"

WHITESPACE			[ \t\n\r\f]+

%%

 /* Comments */
"//".*				{ 
						/* single-line comment */
						if(DEBUG) printf("Eat up comment at line %d\n", yylineno);
					}

"/*"				{
						/* multi-line comment */ 
						if(DEBUG) printf("Eat up comment from line %d ", yylineno);
						BEGIN(ML_COMMENT);
					} 
<ML_COMMENT>"*/" 	{
						if(DEBUG) printf("to line %d\n", yylineno);
						BEGIN(INITIAL);
					}
<ML_COMMENT>[^*\n]+
<ML_COMMENT>"*"
<ML_COMMENT>"\n"


 /* Keywords */
"break"				{ return T_BREAK; }
"char"      		{ return T_CHAR; }
"continue"			{ return T_CONTINUE; }
"double"			{ return T_DOUBLE; }
"else"				{ return T_ELSE; }
"float"				{ return T_FLOAT; }
"for"				{ return T_FOR; }
"if"				{ return T_IF; }
"int"				{ return T_INT; }
"return"			{ return T_RETURN; }
"void"				{ return T_VOID; }
"while"				{ return T_WHILE; }

"input"				{ return T_INPUT; }
"main"				{ return T_MAIN; }
"print"				{ return T_PRINT; }


 /* Operators */
"="					{ yylval.op_type = ASSIGN; 			return T_ASSIGN; }

"++"				{ yylval.op_type = INC; 			return T_INCDEC; }
"--"				{ yylval.op_type = DEC; 			return T_INCDEC; }

"+"					{ yylval.op_type = ADD; 			return T_ADDOP; }
"-"					{ yylval.op_type = SUB; 			return T_ADDOP; }
"*"					{ yylval.op_type = MUL; 			return T_MULOP; }
"/"					{ yylval.op_type = DIV; 			return T_MULOP; }
"%"					{ yylval.op_type = REM; 			return T_MULOP; }

"||"				{ yylval.op_type = OR; 				return T_OROP; }
"&&"				{ yylval.op_type = AND; 			return T_ANDOP; }
"!"					{ yylval.op_type = NOT; 			return T_NOTOP; }

"=="				{ yylval.op_type = EQUAL; 			return T_EQUOP; }
"!="				{ yylval.op_type = NOT_EQUAL; 		return T_EQUOP; }
">"					{ yylval.op_type = GREATER; 		return T_RELOP; }
"<"					{ yylval.op_type = LESS; 			return T_RELOP; }
">="				{ yylval.op_type = GREATER_EQUAL; 	return T_RELOP; }
"<="				{ yylval.op_type = LESS_EQUAL; 		return T_RELOP; }


 /* Other tokens */
"("					{ return T_LPAREN; }
")"					{ return T_RPAREN; }
"{"					{ return T_LBRACE; }
"}"					{ return T_RBRACE; }
","					{ return T_COMMA; }
";"					{ return T_SEMI; }


 /* Identifiers, Constants, Strings */
{ID} 				{ yylval.sval = to_id(yytext, yyleng);			return T_ID;	 }
{ICONST} 			{ yylval.val.ival = atoi(yytext); 				return T_ICONST; }
{FCONST} 			{ yylval.val.fval = atof(yytext); 				return T_FCONST; }
{CCONST} 			{ yylval.val.cval = to_char(yytext); 			return T_CCONST; }
{STRING} 			{ yylval.sval = to_string(yytext, yyleng);		return T_STRING; }


 /* Whitespace */
{WHITESPACE}		{ /* ignore */ }


 /* Unrecognized tokens - Error */
.					{
						fprintf(stderr, "Lexical error at line %d. Unrecognized Token: \"%s\"\n",
									yylineno, yytext);
    					exit(EXIT_FAILURE);
					}

%%

char *to_id(char *str_in, int len) {
    char *str_out;

    str_out = (char *)malloc((len + 1) * sizeof(char));

    strncpy(str_out, str_in, len);

    return str_out;
}

char to_char(char *str) {
    /* Known escape sequence */
    if (str[1] == '\\') {
        switch (str[2]) {
        case 'n':
            return '\n';
		case 'f':
            return '\f';
		case 't':
            return '\t';
        case 'r':
            return '\r';
		case 'b':
            return '\b';
        case 'v':
            return '\v';
		/*
			No default case is needed.
			Lexer treats other escape sequences as unrecognized tokens.
		*/
        }
    }
	/* Not an escape sequence */
    return str[1];
}

char *to_string(char *str_in, int len) {
    char *str_out;

    str_out = (char *)malloc((len - 1) * sizeof(char));

    strncpy(str_out, &str_in[1], len - 2);

    return str_out;
}