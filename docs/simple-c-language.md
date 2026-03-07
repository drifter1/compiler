# Simple C Language

The language Simple C is similar to the high-level programming language [C](https://www.c-language.org/) and is described in detail in this document. It is a simplified version of C, designed purely for educational purposes. In opposition to C, functions do not require declaration before use. There is also no main function. A program in this language begins with variable declarations for the main function and continues with statements for the main function. A return statement then ends the main function. Finally, optional function declarations are included at the end. Of course, using a function other than the built-in `print()` without subsequently declaring/defining it yields an error.

## Terminal Symbols (or Lexical Units)

### Keywords

- `char` -> to define char datatype
- `int` -> to define int datatype
- `float` -> to define float datatype
- `double` -> to define double datatype
- `if` -> for conditional statement declaration
- `else` -> else condition
- `while` -> while loop declaration
- `for` -> for loop declaration
- `continue` -> to get to the next iteration of a loop
- `break` -> to break out of a loop
- `void` -> to declare void datatype or function that doesn't return
- `return` -> return to function that called (maybe even with return-value) or to the operating system

### Operators

#### Mathematical Operators
- `+` -> addition (**ADDOP** of type *ADD*)
- `-` -> subtraction (**ADDOP** of type *SUB*)
- `*` -> multiplication (**MULOP**)
- `/` -> division (**DIVOP**)
- `++` -> increment by 1 (**INCDEC** of type *INC*)
- `--` -> decrement by 1 (**INCDEC** of type *DEC*)

#### Logical Operators
- `||` -> logical or (**OROP**)
- `&&` -> logical and (**ANDOP**)
- `!` -> logical not (**NOTOP**)

#### Relational Operators
- `==` -> equality (**EQUOP** of type *EQUAL*)
- `!=` -> inequality (**EQUOP** of type *NOT_EQUAL*)
- `>` -> greater (**RELOP** of type *GREATER*)
- `<` -> less (**RELOP** of type *LESS*)
- `>=` -> greater equal (**RELOP** of type *GREATER_EQUAL*)
- `<=` -> less equal (**RELOP** of type *LESS_EQUAL*)

### Identifiers

A valid identifier (**ID**) must start with at least one alphabetical letter and may be followed by any number of letters or digits.

### Constants

An integer constant (**ICONST**) is either the literal 0 or a sequence of digits that does not begin with 0.

A floating-point constant (**FCONST**) is either the literal 0, or a number with a decimal point and at least one digit after it. It may have zero or more digits before the decimal point.

A character constant (**CCONST**) is either a single printable ASCII character or one of the common escape sequences (e.g. `\n`, `\f`, `\t`, `\r`, `\b`, `\v`) enclosed in single quotes `'`,

### String

A string (**STRING**) is a sequence of zero or more printable ASCII characters enclosed within double quotes `"`.

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

- **array**: LBRACK expression RBRACK ;

- **init**:	var_init | array_init ; 

- **var_init** : ID ASSIGN constant ;

- **array_init**: ID array ASSIGN LBRACE values RBRACE ;

- **values**: values COMMA constant | constant ;

### Statements

- **statements**: statements statement | statement ;

- **statement**: if_statement | for_statement | while_statement	| assigment SEMI | CONTINUE SEMI | BREAK SEMI | function_call SEMI | ID INCDEC SEMI | INCDEC ID SEMI ;

- **if_statement**: IF LPAREN expression RPAREN tail else_if optional_else | IF LPAREN expression RPAREN tail optional_else ;

- **else_if**: else_if ELSE IF LPAREN expression RPAREN tail | ELSE IF LPAREN expression RPAREN tail ;

- **optional_else** : ELSE tail	| ;

- **for_statement**: FOR LPAREN assigment SEMI expression SEMI ID INCDEC RPAREN tail ;

- **while_statement**: WHILE LPAREN expression RPAREN tail ;

- **tail**: LBRACE statements RBRACE ;

- **expression**: expression ADDOP expression | expression MULOP expression | expression DIVOP expression | ID INCDEC | INCDEC ID | expression OROP expression | expression ANDOP expression | NOTOP expression | expression EQUOP expression | expression RELOP expression	| LPAREN expression RPAREN | var_ref | constant | ADDOP constant %prec MINUS | function_call ;

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

## Semantics

### Data Types

### Declarations

### Initializations

### Function Declarations

### Expressions

### Precedencies and Associativities

### Statements
