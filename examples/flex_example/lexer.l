%{
	#include <stdio.h>
    #include <stdlib.h>

    int yylex();
    void ret_print(char *token_type);
%}

%option yylineno noyywrap noinput nounput never-interactive

alpha 		[a-zA-Z]
digit 		[0-9]
alnum 		{alpha}|{digit}

ID 			{alpha}+{alnum}*
ICONST		"0"|[0-9]{digit}*
FCONST		"0"|{digit}*"."{digit}+

%%

"//".*			{ printf("Eat up comment at line %d\n", yylineno); } 

{ID} 		    { ret_print("ID"); }
{ICONST} 	    { ret_print("ICONST"); }
{FCONST} 	    { ret_print("FCONST"); }

[ \t\r\f]+		/* eat up whitespace */
"\n"			
"<<EOF>>"		{ return EXIT_SUCCESS; }

.				{
					fprintf(stderr, "Lexical error at line %d. Unrecognized Token: \"%s\"\n",
							yylineno, yytext);
    				exit(EXIT_FAILURE);
				}

%%

void ret_print(char *token_type){
    printf("yytext: %s\ttoken: %s\tlineno: %d\n", yytext, token_type, yylineno);
}

int main(int argc, char *argv[]){

    if (argc == 2) {
        if (!(yyin = fopen(argv[1], "r"))) {
            fprintf(stderr, "Unable to open file %s\n", argv[1]);
            exit(EXIT_FAILURE);
        }

        yylex();

        fclose(yyin);

        return EXIT_SUCCESS;
    }

    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);

    return EXIT_FAILURE;
}