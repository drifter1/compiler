# Simple C Language

## Tokens

### Keywords

- `char` or `CHAR` -> to define char datatype
- `int` or `INT` -> to define int datatype
- `float` or `FLOAT` -> to define float datatype
- `double` or `DOUBLE` -> to define double datatype
- `if` or `IF` -> for conditional statement declaration
- `else` or `ELSE` -> else condition
- `while` or `WHILE` -> while loop declaration
- `for` or `FOR` -> for loop declaration
- `continue` or `CONTINUE` -> to get to the next iteration of a loop
- `break` or `BREAK` -> to break out of a loop
- `void` or `VOID` -> to declare void datatype or function that doesn't return
- `return` or `RETURN` -> return to function that called (maybe even with return-value) or to the operating system

### Operators

- `+` -> addition (**ADDOP** of type *ADD*)
- `-` -> subtraction (**ADDOP** of type *SUB*)
- `*` -> multiplication (**MULOP**)
- `/` -> division (**DIVOP**)
- `++` -> increment by 1 (**INCR** of type *INC*)
- `--` -> decrement by 1 (**INCR** of type DE*C)
- `||` -> or (**OROP**)
- `&&` -> and (**ANDOP**)
- `!` -> not (**NOTOP**)
- `==` -> equality (**EQUOP** of type *EQUAL*)
- `!=` -> inequality (**EQUOP** of type *NOT_EQUAL*)
- `>` -> greater (**RELOP** of type *GREATER*)
- `<` -> less (**RELOP** of type *LESS*)
- `>=` -> greater equal (**RELOP** of type *GREATER_EQUAL*)
- `<=` -> less equal (**RELOP** of type *LESS_EQUAL*)

### Identifiers, Constants and Strings

- Identifier (**ID**) 
- Integer constant (**ICONST**)
- Floating point constant (**FCONST**)
- Printable ASCII character within single quotes `'` (**CCONST**)
- Printable ASCII character within double quotes `"` (**STRING**)

### Other Tokens

- `(` and `)` -> parentheses (**LPAREN**, **RPAREN**)
- `[` and `]` -> brackets (**LBRACK**, **RBRACK**)
- `{` and `}` -> bracelets (**LBRACE**, **RBRACE**)
- `;` -> semicolon (**SEMI**)
- `,` -> comma (**COMMA**)
- `=` -> assignment (**ASSIGN**)
- `&` -> reference (**REFER**)
- `(EOF)` -> end of file

### Comments

- `//` -> single-line comment
- Text between `/*` and `*/` -> multi-line comment

## Grammar

- **program**: declarations statements RETURN SEMI functions_optional ;

### Declarations

- **declarations**: declarations declaration | declaration ;

- **declaration**: type names SEMI ;

- **type**: INT | CHAR | FLOAT | DOUBLE | VOID ;

- **names**: names COMMA variable | names COMMA init | variable	| init ;

- **variable**: ID | pointer ID | ID array ;

- **pointer**: MULOP ;

- **array**: LBRACK expression RBRACK | LBRACK ICONST RBRACK ;

- **init**:	var_init | array_init ; 

- **var_init** : ID ASSIGN constant ;

- **array_init**: ID array ASSIGN LBRACE values RBRACE ;

- **values**: values COMMA constant | constant ;

### Statements

- **statements**: statements statement | statement ;

- **statement**: if_statement | for_statement | while_statement	| assigment SEMI | CONTINUE SEMI | BREAK SEMI | function_call SEMI | ID INCR SEMI | INCR ID SEMI ;

- **if_statement**: IF LPAREN expression RPAREN tail else_if optional_else | IF LPAREN expression RPAREN tail optional_else ;

- **else_if**: else_if ELSE IF LPAREN expression RPAREN tail | ELSE IF LPAREN expression RPAREN tail ;

- **optional_else** : ELSE tail	| ;

- **for_statement**: FOR LPAREN assigment SEMI expression SEMI ID INCR RPAREN tail ;

- **while_statement**: WHILE LPAREN expression RPAREN tail ;

- **tail**: LBRACE statements RBRACE ;

- **expression**: expression ADDOP expression | expression MULOP expression | expression DIVOP expression | ID INCR | INCR ID | expression OROP expression | expression ANDOP expression | NOTOP expression | expression EQUOP expression | expression RELOP expression	| LPAREN expression RPAREN | var_ref | constant | ADDOP constant %prec MINUS | function_call ;

- **constant**: ICONST  | FCONST | CCONST ;

- **assigment**: var_ref ASSIGN expression ;

- **var_ref**: variable | REFER variable ;

- **function_call**: ID LPAREN call_params RPAREN ;

- **call_params**: call_param | STRING | ;

- **call_param**: call_param COMMA expression | expression ;

### Functions (optional)

- **functions_optional**: functions | ;

- **functions**: functions function | function ;

- **function**: function_head function_tail ;

- **function_head**: return_type ID LPAREN parameters_optional RPAREN ;

- **return_type**: type | type pointer ;

- **parameters_optional**: parameters | ;

- **parameters**: parameters COMMA parameter | parameter ;

- **parameter**: type variable ;

- **function_tail**: LBRACE declarations_optional statements_optional return_optional RBRACE ;

- **declarations_optional**: declarations | ;

- **statements_optional**: statements | ;

- **return_optional**: RETURN expression SEMI | ;
