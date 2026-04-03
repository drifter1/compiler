%{
	#include "../include/compiler.h"
	#include "../build/parser.tab.h"

	char *to_id(const char *str_in, int len);
	char to_char(const char *str);
	char *to_string(const char *str_in, int len);
	void print_token(const char *token);
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
						#if DEBUG
						printf("Eat up comment at line %d\n", yylineno);
						#endif
					}

"/*"				{
						/* multi-line comment */ 
						#if DEBUG
						printf("Eat up comment from line %d ", yylineno);
						#endif
						BEGIN(ML_COMMENT);
					} 
<ML_COMMENT>"*/" 	{
						#if DEBUG
						printf("to line %d\n", yylineno);
						#endif
						BEGIN(INITIAL);
					}
<ML_COMMENT>[^*\n]+
<ML_COMMENT>"*"
<ML_COMMENT>"\n"
<ML_COMMENT><<EOF>>	{
						fprintf(stderr, "Lexical error at line %d. EOF in comment\n",
									yylineno);
    					exit(EXIT_FAILURE);
					}

 /* Keywords */
"break"				{ print_token("T_BREAK");		return T_BREAK;		}
"char"      		{ print_token("T_CHAR");		return T_CHAR;		}
"continue"			{ print_token("T_CONTINUE");	return T_CONTINUE;	}
"double"			{ print_token("T_DOUBLE");		return T_DOUBLE;	}
"else"				{ print_token("T_ELSE");		return T_ELSE;		}
"float"				{ print_token("T_FLOAT");		return T_FLOAT;		}
"for"				{ print_token("T_FOR");			return T_FOR;		}
"if"				{ print_token("T_IF");			return T_IF;		}
"int"				{ print_token("T_INT");			return T_INT;		}
"return"			{ print_token("T_RETURN");		return T_RETURN;	}
"void"				{ print_token("T_VOID");		return T_VOID;		}
"while"				{ print_token("T_WHILE");		return T_WHILE;		}

"input"				{ print_token("T_INPUT");		return T_INPUT;		}
"main"				{ print_token("T_MAIN");		return T_MAIN;		}
"print"				{ print_token("T_PRINT");		return T_PRINT;		}


 /* Operators */
"="					{ print_token("T_ASSIGN");	yylval.op_type = ASSIGN; 			return T_ASSIGN; }

"++"				{ print_token("T_INCDEC");	yylval.op_type = INC; 				return T_INCDEC; }
"--"				{ print_token("T_INCDEC");	yylval.op_type = DEC; 				return T_INCDEC; }

"+"					{ print_token("T_ADDOP"); 	yylval.op_type = ADD; 				return T_ADDOP;  }
"-"					{ print_token("T_ADDOP");	yylval.op_type = SUB; 				return T_ADDOP;  }
"*"					{ print_token("T_ADDOP"); 	yylval.op_type = MUL; 				return T_MULOP;  }
"/"					{ print_token("T_MULOP"); 	yylval.op_type = DIV; 				return T_MULOP;  }
"%"					{ print_token("T_MULOP"); 	yylval.op_type = REM; 				return T_MULOP;  }

"||"				{ print_token("T_OROP");	yylval.op_type = OR; 				return T_OROP;   }
"&&"				{ print_token("T_ANDOP"); 	yylval.op_type = AND; 				return T_ANDOP;  }
"!"					{ print_token("T_NOTOP"); 	yylval.op_type = NOT; 				return T_NOTOP;  } 

"=="				{ print_token("T_EQUOP");	yylval.op_type = EQUAL; 			return T_EQUOP;  }
"!="				{ print_token("T_EQUOP");	yylval.op_type = NOT_EQUAL; 		return T_EQUOP;  }
">"					{ print_token("T_RELOP");	yylval.op_type = GREATER; 			return T_RELOP;  }
"<"					{ print_token("T_RELOP");	yylval.op_type = LESS; 				return T_RELOP;  }
">="				{ print_token("T_RELOP");	yylval.op_type = GREATER_EQUAL;		return T_RELOP;  }
"<="				{ print_token("T_RELOP");	yylval.op_type = LESS_EQUAL; 		return T_RELOP;  }


 /* Other tokens */
"("					{ print_token(" T_LPAREN");	return T_LPAREN; }
")"					{ print_token(" T_RPAREN");	return T_RPAREN; }
"{"					{ print_token("T_LBRACE");	return T_LBRACE; }
"}"					{ print_token("T_RBRACE");	return T_RBRACE; }
","					{ print_token("T_COMMA");	return T_COMMA;  }
";"					{ print_token(" T_SEMI");	return T_SEMI;   }


 /* Identifiers, Constants, Strings */
{ID} 				{ print_token("T_ID");		yylval.sval = to_id(yytext, yyleng);		return T_ID;	 }
{ICONST} 			{ print_token("T_ICONST");	yylval.val.ival = atoi(yytext); 			return T_ICONST; }
{FCONST} 			{ print_token("T_FCONST");	yylval.val.fval = atof(yytext); 			return T_FCONST; }
{CCONST} 			{ print_token("T_CCONST");	yylval.val.cval = to_char(yytext); 			return T_CCONST; }
{STRING} 			{ print_token("T_STRING");	yylval.sval = to_string(yytext, yyleng);	return T_STRING; }


 /* Whitespace */
{WHITESPACE}		{ print_token(yytext); }


 /* Unrecognized tokens - Error */
.					{
						fprintf(stderr, "Lexical error at line %d. Unrecognized Token: \"%s\"\n",
									yylineno, yytext);
    					exit(EXIT_FAILURE);
					}

%%

char *to_id(const char *str_in, int len) {
    char *str_out;

    str_out = (char *)malloc((len + 1) * sizeof(char));

    strncpy(str_out, str_in, len);

    return str_out;
}

char to_char(const char *str) {
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

char *to_string(const char *str_in, int len) {
    char *str_out;

    str_out = (char *)malloc((len - 1) * sizeof(char));

    strncpy(str_out, &str_in[1], len - 2);

    return str_out;
}

void print_token(const char *token){
#if DEBUG
	fprintf(lexer_dump_file, "%s", token);
#endif
}