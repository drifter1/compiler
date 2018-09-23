program: declarations statements ;
declarations: declarations declaration | declaration;
declaration: type names ';' ;
type: INT | CHAR | FLOAT | DOUBLE | VOID;
names: variable | names ',' variable;
variable: ID |
    ('*')+ID |
    ID('['ICONST']')+
;
statements: statements statement | statement;
statement:
if_statement | for_statement | while_statement | assigment |
CONTINUE | BREAK | RETURN
;
if_statement:
IF '(' expression ')' tail
(ELSE IF '(' expression ')' tail)*
(ELSE tail)?
;
for_statement: FOR '(' expression ';' expression ';' expression ')' tail ;
while_statement: WHILE '(' bool_expression ')' tail ;
tail: statement | '{' statements '}' ;
expression:
    expression '+' expression |
    expression '-' expression |
    expression '*' expression |
    expression '/' expression |
    expression '++' |
    expression '--' |
    '++' expression |
    '--' expression |
    expression '||' expression |
    expression '&&' expression |
    '!' expression |
    expression '==' expression |
    expression '!=' expression |
    expression '>' expression |
    expression '<' expression |
    expression '>=' expression |
    expression '<=' expression |
    '(' expression ')' |
    variable |
    '-'? constant
;
constant: ICONST | FCONST | CCONST ;
assigment: '&'? variable '=' expression ';' ; 
