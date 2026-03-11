%{
	#include "../include/compiler.h"
	#include "../build/parser.tab.h"
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

%%

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


"char"      		{ return CHAR; }
"int"				{ return INT; }
"float"				{ return FLOAT; }
"double"			{ return DOUBLE; }
"if"				{ return IF; }
"else"				{ return ELSE; }
"while"				{ return WHILE; }
"for"				{ return FOR; }
"continue"			{ return CONTINUE; }
"break"				{ return BREAK; }
"void"				{ return VOID; }
"return"			{ return RETURN; }


"+"					{ yylval.val.ival = ADD; return ADDOP; }
"-"					{ yylval.val.ival = SUB; return ADDOP; }
"*"					{ return MULOP; }
"/"					{ return DIVOP; }
"++"				{ yylval.val.ival = INC; return INCDEC; }
"--"				{ yylval.val.ival = DEC; return INCDEC; }
"||"				{ return OROP; }
"&&"				{ return ANDOP; }
"!"					{ return NOTOP; }
"=="				{ yylval.val.ival = EQUAL; return EQUOP; }
"!="				{ yylval.val.ival = NOT_EQUAL; return EQUOP; }
">"					{ yylval.val.ival = GREATER; return RELOP; }
"<"					{ yylval.val.ival = LESS; return RELOP; }
">="				{ yylval.val.ival = GREATER_EQUAL; return RELOP; }
"<="				{ yylval.val.ival = LESS_EQUAL; return RELOP; }


"("					{ return LPAREN; }
")"					{ return RPAREN; }
"["					{ return LBRACK; }
"]"					{ return RBRACK; }
"{"					{ return LBRACE; }
"}"					{ return RBRACE; }
";"					{ return SEMI; }
","					{ return COMMA; }
"="					{ return ASSIGN; }
"&"					{ return REFER; }


{ID} 				{
						// insert identifier into symbol table
						insert(yytext, strlen(yytext), UNDEF, yylineno);
						yylval.symtab_item = lookup(yytext);
						return ID;
					}
{ICONST} 			{ yylval.val.ival = atoi(yytext); return ICONST; }
{FCONST} 			{ yylval.val.fval = atof(yytext); return FCONST; }
{CCONST} 			{ yylval.val.cval = yytext[0];    return CCONST; }
{STRING} 			{
						yylval.val.sval = malloc(yyleng * sizeof(char) + 1);
						strcpy(yylval.val.sval , yytext);	return STRING;
					}


[ \t\r\f]+			/* eat up whitespace */
"\n"			
"<<EOF>>"			{ return 0; }
.					{
						fprintf(stderr, "Lexical error at line %d. Unrecognized Token: \"%s\"\n",
									yylineno, yytext);
    					exit(EXIT_FAILURE);
					}

%%
