# Simple C Language

The language Simple C is similar to the high-level programming language [C](https://www.c-language.org/) and is described in as much detail as possible in this document. It is a simplified version of C, designed purely for educational purposes. The functionality and keyword coverage are both very limited. There are no preprocessor directives. Only basic types are supported. A program in this language begins with optional global variable declarations, followed by optional function declarations and finally the declaration of the main function. Contrary to C, the special identifier `main` of the main function is reserved as a keyword. The body of functions has a strict order. The body starts with optional variable declarations, followed by statements. Built-in `print` and `input` statements (with reserved keyword) make it possible to interact with standard output and input, respectively. This enables the output of strings and expression values, as well as the capture of user input into variables.

> [!IMPORTANT]
> Please bear in mind that this documentation is still a work in progress. The language described is also not identical to the current implementation.

## Terminal Symbols (or Lexical Units)

### Keywords

#### C Keywords

|  Keyword   |               Usage                |
| :--------: | :--------------------------------: |
| `break`    | Declaration of break statement     |
| `char`     | Type specifier for character types |
| `continue` | Declaration of continue statement  |
| `double`   | Type specifier for double types    |
| `else`     | Declaration of alternative branch  |
| `float`    | Type specifier for float types     |
| `for`      | Declaration of for loop            |
| `if`       | Declaration of if statement        |
| `int`      | Type specifier for int types       |
| `return`   | Declaration of return statement    |
| `void`     | Type specifier for void types      |
| `while`    | Declaration of while loop          |

#### Supplementary Keywords

|  Keyword |             Usage              |
| :------: | :----------------------------: |
| `input`  | Declaration of input statement |
| `main`   | Identifier of main function    |
| `print`  | Declaration of print statement |

### Operators

#### Assignment Operator

- `=` → assignment (**ASSIGN**)

#### Increment/Decrement Operators

- `++` → increment by 1 (**INCDEC** of type *INC*)
- `--` → decrement by 1 (**INCDEC** of type *DEC*)

> [!NOTE]
> The increment (`++`) and decrement (`--`) operators can be applied as prefix or suffix operations, e.g. `++a` or `a++`.

#### Arithmetic Operators

- `+` → addition (**ADDOP** of type *ADD*)
- `-` → subtraction (**ADDOP** of type *SUB*)
- `*` → multiplication (**MULOP** of type *MUL*)
- `/` → division (**MULOP** of type *DIV*)
- `%` → remainder (**MULOP** of type *REM*)

> [!NOTE]
> The lexical units `+` and `-` are also used for the unary plus and unary minus operations, i.e. `+1` or `-1`.

#### Logical Operators

- `||` → logical or (**OROP**)
- `&&` → logical and (**ANDOP**)
- `!` → logical not (**NOTOP**)

#### Relational Operators

- `==` → equality (**EQUOP** of type *EQUAL*)
- `!=` → inequality (**EQUOP** of type *NOT_EQUAL*)
- `>` → greater (**RELOP** of type *GREATER*)
- `<` → less (**RELOP** of type *LESS*)
- `>=` → greater equal (**RELOP** of type *GREATER_EQUAL*)
- `<=` → less equal (**RELOP** of type *LESS_EQUAL*)

### Other Tokens

- `(` → left parenthesis (**LPAREN**)
- `)` → right parenthesis (**RPAREN**)
- `{` → left curly brace (**LBRACE**)
- `}` → right curly brace (**RBRACE**)
- `,` → comma (**COMMA**)
- `;` → semicolon (**SEMI**)
- `<<EOF>>` → end of file

### Identifiers

A valid identifier (**ID**) must start with at least one alphabetical letter and may be followed by any number of letters or digits. Special characters are not allowed, nor can it be a reserved keyword.

<details>
    <summary><b>Valid examples</b></summary>

```
a           → is a letter
foo         → contains only letters
x1          → starts with a letter and is followed by a digit
y55         → starts with a letter and is followed by digits
e1a2b       → starts with a letter and is followed by digits and letters 
```

</details>

<details>
    <summary><b>Invalid examples</b></summary>

```
3xy         → starts with a digit
e$          → contains a special character
my-var      → contains a special character
@value      → contains and also starts with a special character
return      → is a reserved keyword
```

</details>

### Constants

#### Integer constant

An integer constant (**ICONST**) is either the literal 0 or a sequence of digits that does not begin with 0. Only digits are permitted. Integer constants must not contain letters or special characters.

<details>
    <summary><b>Valid examples</b></summary>

```
0           → is the literal zero
10          → begins with non-zero digit and is followed by zero
191         → begins with non-zero digit and is followed by digits
```

</details>

<details>
    <summary><b>Invalid examples</b></summary>

```
02          → begins with 0 but is followed by a digit
034         → begins with 0 but is followed by digits
18t         → begins with non-zero digit, but contains letter
```

</details>

#### Floating-point constant

A floating-point constant (**FCONST**) contains a decimal point, with digits either before and after it, or only before or after it. Before the decimal point, there can be either the literal 0 or a sequence of digits that does not start with 0.

<details>
    <summary><b>Valid examples</b></summary>

```
0.          → literal 0 followed by decimal point
.0          → decimal point followed by literal 0
0.0         → literal 0 followed by decimal point followed by literal 0
.52         → decimal point followed by digits
2.          → digit followed by decimal point 
3.14        → digit followed by decimal point followed by digits
```

</details>

<details>
    <summary><b>Invalid examples</b></summary>

```
.           → a single decimal point
02.         → begins with 0 and includes another digit before the decimal point
045.1       → begins with 0 and includes further digits before the decimal point
```

</details>

#### Character constant

A character constant (**CCONST**) is either a single printable ASCII character or one of the common escape sequences (e.g. `\n`, `\f`, `\t`, `\r`, `\b`, `\v`) enclosed in single quotes `'`,

<details>
    <summary><b>Valid examples</b></summary>

```
'a'         → printable ASCII character enclosed in single quotes
'\n'        → escape sequence enclosed in single quotes
```

</details>

<details>
    <summary><b>Invalid examples</b></summary>

```
c           → printable ASCII character but not enclosed in single quotes
\t          → escape sequence but not enclosed in single quotes
'␀'         → non-printable character enclosed in single quotes
```

</details>

### String

A string (**STRING**) is a sequence of zero or more printable ASCII characters enclosed within double quotes `"`.

<details>
    <summary><b>Valid examples</b></summary>

```
"s"         → printable ASCII character enclosed in double quotes
"text"      → printable ASCII characters enclosed in double quotes
```

</details>

<details>
    <summary><b>Invalid examples</b></summary>

```
pi          → printable ASCII characters but not enclosed in double quotes
"la␀"       → double quote enclosed sequence includes non-printable character
```

</details>

### Comments

- `//` → single-line comment
- Text between `/*` and `*/` → multi-line comment


## Grammar

- **program** → declarations functions main_function | declarations main_function | functions main_function | main_function ;

- **declarations** → declarations declaration | declaration ;

- **declaration** → type names SEMI ;

- **type** → INT | CHAR | FLOAT | DOUBLE | VOID ;

- **names** → names COMMA var_init | var_init ;

- **var_init** → variable init ;

- **variable** → ID ;

- **init** →  ASSIGN constant | /* empty */ ;

- **constant** → ICONST  | FCONST | CCONST ;

- **functions** → functions function | function ;

- **function** → function_head function_tail ;

- **function_head** → type ID LPAREN parameters RPAREN | type ID LPAREN RPAREN ;

- **parameters** → parameters COMMA parameter | parameter ;

- **parameter** → type variable ;

- **function_tail** → LBRACE declarations statements RBRACE | LBRACE statements RBRACE;

- **statements** → statements statement | statement ;

- **statement** → if_statement | for_statement | while_statement | assignment SEMI | CONTINUE SEMI | BREAK SEMI | function_call SEMI | var_ref INCDEC SEMI | INCDEC var_ref SEMI | print_statement | input_statement | return_statement ;

- **if_statement** → IF LPAREN expression RPAREN tail else_if optional_else | IF LPAREN expression RPAREN tail optional_else ;

- **expression** → expression ADDOP expression | expression MULOP expression | expression DIVOP expression | var_ref INCDEC | INCDEC var_ref | expression OROP expression | expression ANDOP expression | NOTOP expression | expression EQUOP expression | expression RELOP expression | LPAREN expression RPAREN | var_ref | constant | ADDOP constant | function_call ;

- **var_ref** → variable ;

- **function_call** → ID LPAREN arguments RPAREN | ID LPAREN RPAREN ;

- **arguments** → arguments COMMA argument | argument ;

- **argument** → var_ref | constant | ADDOP constant ;

- **tail** → LBRACE statements RBRACE ;

- **else_if** → else_if ELSE IF LPAREN expression RPAREN tail | ELSE IF LPAREN expression RPAREN tail ;

- **optional_else** → ELSE tail	| /* empty */ ;

- **for_statement** → FOR LPAREN assignment SEMI expression SEMI var_ref INCDEC RPAREN tail ;

- **assignment** → var_ref ASSIGN expression ;

- **while_statement** → WHILE LPAREN expression RPAREN tail ;

- **print_statement** → PRINT expression SEMI | PRINT STRING SEMI ;

- **input_statement** → INPUT var_ref SEMI ;

- **return_statement** → RETURN expression SEMI | RETURN SEMI ;

- **main_function** → main_head function_tail ;

- **main_head** → INT MAIN LPAREN RPAREN ;

<details>
    <summary><b>Example program</b></summary>

```c
// global variable declaration
int x;
// function declarations
int func1(){            /* no parameters, with return */
    // no declaration
	return 5 + x;       
}
void func2(char c){     /* one parameter, no return */
	char s;
    s = c;
	print s;
}
double add (double a, int b){   /* two parameters, with return */
    double res;
    res = a + b + (-5);
    res = res % x;
    return res;
}
// main function declaration
int main() {
    // declarations
    int i;                      /* declaration without init */
    char c = 'c';               /* declaration with init */
    double val = 2.5, res;      /* two declarations, one with init */
    // statements
    input x;                    /* input statement */
    for(i = 0; i < 10; i++){    /* for loop */
        if(i > 5){              /* conditional statement */
            break;
        }
        else if(i == 5){        /* conditional branch */
            i = 2 * i - x;
            val = func1();
            res = add(val, i);
            print res;
            print "\n";
            continue;
        }
        else{                   /* else branch */
            res = add(val, i);
            val = res + 0.5;
            print res;
            print "\n";
        }
    }

    while(i < 12){              /* while loop */
        print i;
        print " ";
        func2(c);
        i++;
    }
    print "\n";                 /* print statement */
    return 0;                   /* return statement */
}
```

</details>

## Semantics

### Data Types

- `int` type → for integer numbers
- `float` type → for single precision floating-point numbers
- `double` type → for double precision floating-point numbers
- `char` type → for characters
- `void` type → for incomplete types

### Type Kinds

- Basic type → declaration type of a variable or function parameter
- Function type → data type of the return value of a function

### Variable Declarations

Variables are declared with a specific type and an identifier (ID) that represents them. It is possible to declare multiple variables of the same type within a single declaration, provided that the identifiers are separated by commas.

<details>
    <summary><b>Examples</b></summary>

```c
int a;
float b, c;
```

</details>

### Variable Initializations

Variables may be initialised during declaration by assigning a constant value to them. If a declaration contains more than one variable, it is possible to assign an initial value to only some of them, with the remainder receiving a default value.

<details>
    <summary><b>Examples</b></summary>

```c
int i = 0;
char c1, c2 = 'u', c3;
```

</details>

### Function Declarations

Functions are declared with a specific return type and an identifier (ID) that represents the function. Optional parameters can be included in the parentheses. A parameter is a pair consisting of a type and an identifier, and parameters are separated by commas. The variable declarations and statements are enclosed in curly braces.

<details>
    <summary><b>Examples</b></summary>

```c
int add(int a, int b) {
    ...
}
void foo() {

}
```

</details>

### Expressions

An expression may contain binary operations (arithmetic, logical, relational), unary operations (increment/decrement, logical NOT, unary minus on constants), parenthesised sub‑expressions, variable references, constants, and non-void function calls.

<details>
    <summary><b>Examples</b></summary>

```c
5 * a + 1
c == d
i < 10
i++
!(a && b)
-5
3.14
add(a, 3)
```

</details>

### Precedencies and Associativities

|        Operator        |                      Description                     | Associativity |
| :--------------------: | :--------------------------------------------------: | :-----------: |
| `,`                    | Comma                                                | Left-to-right |
| `=`                    | Assignment                                           | Right-to-left |
| `\|\|`                 | Logical OR                                           | Left-to-right |
| `&&`                   | Logical AND                                          | Left-to-right |
| `==`, `!=`             | Equality/Inequality operators                        | Left-to-right |
| `<`, `<=`, `>`, `>=`   | Relational operators                                 | Left-to-right |
| `+`, `-`               | Addition and subtraction                             | Left-to-right |
| `*`, `/`, `%`          | Multiplication, division and remainder               | Left-to-right |
| `!`, `++`, `--`, `-`   | Logical NOT, prefix increment/decrement, unary minus | Right-to-left |
| `()`, `++`, `--`       | Function call, suffix increment/decrement            | Left-to-right |

> [!NOTE]
> The above table is arranged in ascending order of precedence, in line with how operator precedence is declared in Bison or Yacc.

### Statements

 In this language, a statement can be one of the following: a conditional, a loop, an assignment, a control-flow keyword (continue/break), a function call, a return statement, a print or input statement, or an increment/decrement operation. Most of the above are terminated with a semicolon (`;`), except for control structures that contain nested statements within bracelets (`{}`).

<details>
    <summary><b>Examples</b></summary>

```c
if (i < 5) { 
    ...
}
else {
    ...
}
for (i = 0; i < 5; i++) {
    ...
    if (i == 3) {
        continue;
    }
}
while (i > 0) {
    ...
    if (i == 8) {
        break;
    }
    ...
}
k = 5 * func1(p) - a;
i++:
print "Message";
print i + 1;
input var;
return 0;
```

</details>