# Simple C Language

The language Simple C is similar to the high-level programming language [C](https://www.c-language.org/) and is described in as much detail as possible in this document. It is a simplified version of C, designed purely for educational purposes. The functionality and keyword coverage are both very limited. There are no preprocessor directives. Only basic types are supported. A program in this language begins with optional global variable declarations, followed by optional function declarations and finally the declaration of the main function. Contrary to C, the special identifier `main` of the main function is reserved as a keyword. The body of functions has a strict order. The body starts with optional variable declarations, followed by statements There are only two types of scopes. Global variables and function declarations are in the global scope, while function parameters and variables declared within a function are only local to that function. Built-in `print` and `input` statements (with reserved keyword) make it possible to interact with standard output and input, respectively. This enables the output of strings and expression values, as well as the capture of user input into variables.

> [!IMPORTANT]
> Please bear in mind that this documentation is still a work in progress.

## Terminal Symbols (or Lexical Units)

The lexical units that also serve as terminal symbols in the Simple C grammar are described below. The corresponding tokens begin with 'T_' and are presented either in a separate table column or within parentheses. Along with the lexical units, there is also a description of Simple C comments. It should be noted that comments are not part of the language’s grammar. Finally, be aware that Simple C is case-sensitive, meaning it distinguishes between uppercase and lowercase letters regardless of whether they form part of a character constant or string.

### Keywords

The words in the tables below are reserved keywords in Simple C and, as they form an integral component of the grammar, cannot be used as identifier names. These are independent lexical units, just like the operators and other terminal symbols.

#### C Keywords

The following keywords are adopted from the C programming language that the Simple C language is based on.

|  Keyword   |               Usage                |      Token     |
| :--------: | :--------------------------------: | :------------: |
| `break`    | Declaration of break statement     | **T_BREAK**    |
| `char`     | Type specifier for character types | **T_CHAR**     |
| `continue` | Declaration of continue statement  | **T_CONTINUE** |
| `double`   | Type specifier for double types    | **T_DOUBLE**   |
| `else`     | Declaration of alternative branch  | **T_ELSE**     |
| `float`    | Type specifier for float types     | **T_FLOAT**    |
| `for`      | Declaration of for loop            | **T_FOR**      |
| `if`       | Declaration of if statement        | **T_IF**       |
| `int`      | Type specifier for int types       | **T_INT**      |
| `return`   | Declaration of return statement    | **T_RETURN**   |
| `void`     | Type specifier for void types      | **T_VOID**     |
| `while`    | Declaration of while loop          | **T_WHILE**    |

#### Supplementary Keywords

The Simple C language also has some keywords that are not borrowed from C. These are used as helpers to simplify the language. 

|  Keyword |             Usage              |    Token    |
| :------: | :----------------------------: | :---------: |
| `input`  | Declaration of input statement | **T_INPUT** |
| `main`   | Identifier of main function    | **T_MAIN**  |
| `print`  | Declaration of print statement | **T_PRINT** |

### Operators

The Simple C language supports a subset of the operations supported by the C programming language. These include assignment, incrementation, decrementation and arithmetic, logical and relational operations.

#### Assignment Operator

- `=` → assignment (**T_ASSIGN** of operator type *ASSIGN*)

#### Increment/Decrement Operators

- `++` → increment by 1 (**T_INCDEC** of operator type *INC*)
- `--` → decrement by 1 (**T_INCDEC** of operator type *DEC*)

> [!NOTE]
> The increment (`++`) and decrement (`--`) operators can be applied as prefix or postfix operations, e.g. `++a` or `a++`. Once the exact type is clear, the operator type is changed to *PRE_INC*, *PRE_DEC*, *POST_INC* or *POST_DEC*, respectively.

#### Arithmetic Operators

- `+` → addition (**T_ADDOP** of operator type *ADD*)
- `-` → subtraction (**T_ADDOP** of operator type *SUB*)
- `*` → multiplication (**T_MULOP** of operator type *MUL*)
- `/` → division (**T_MULOP** of operator type *DIV*)
- `%` → remainder (**T_MULOP** of operator type *REM*)

> [!NOTE]
> The lexical units `+` and `-` are also used for the unary plus and unary minus operations, i.e. `+1` or `-1`. When the addition or subtraction operators are used as unary operators, the operator type changes to *UNARY_PLUS* or *UNARY_MINUS*, respectively.

#### Logical Operators

- `||` → logical or (**T_OROP** of operator type *OR*)
- `&&` → logical and (**T_ANDOP** of operator type *AND*)
- `!` → logical not (**T_NOTOP** of operator type *NOT*)

#### Relational Operators

- `==` → equality (**T_EQUOP** of operator type *EQUAL*)
- `!=` → inequality (**T_EQUOP** of operator type *NOT_EQUAL*)
- `>` → greater (**T_RELOP** of operator type *GREATER*)
- `<` → less (**T_RELOP** of operator type *LESS*)
- `>=` → greater equal (**T_RELOP** of operator type *GREATER_EQUAL*)
- `<=` → less equal (**T_RELOP** of operator type *LESS_EQUAL*)

### Other Tokens

The following are other characters that are treated as independent lexical units. Depending on the grammar and semantics of the Simple C language, they may sometimes behave like operators. 

- `(` → left parenthesis (**T_LPAREN**)
- `)` → right parenthesis (**T_RPAREN**)
- `{` → left curly brace (**T_LBRACE**)
- `}` → right curly brace (**T_RBRACE**)
- `,` → comma (**T_COMMA**)
- `;` → semicolon (**T_SEMI**)
- `<<EOF>>` → end of file

> [!NOTE]
> The lexical unit `<<EOF>>` is a special character that is treated in a unique way by each system. It is not part of the grammar, but it must be returned by the lexical analyser (usually with the value 0) to indicate the end of syntax analysis.

### Identifiers

A valid identifier (**T_ID**) must start with at least one alphabetical letter and may be followed by any number of letters or digits. Special characters are not allowed, nor can it be a reserved keyword.

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

#### Unsigned integer constant

An unsigned integer constant (**T_ICONST**) is either the literal 0 or a sequence of digits that does not begin with 0. Only digits are permitted. Unsigned integer constants must not contain letters or special characters.

> [!NOTE]
> Of course, the language supports negative values. These values are obtained by applying a unary minus operation.

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

#### Unsigned floating-point constant

An unsigned floating-point constant (**T_FCONST**) contains a decimal point, with digits either before and after it, or only before or after it. Before the decimal point, there can be either the literal 0 or a sequence of digits that does not start with 0.

> [!NOTE]
> Of course, the language supports negative values. These values are obtained by applying a unary minus operation.

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

A character constant (**T_CCONST**) is either a single printable ASCII character or one of the common escape sequences (e.g. `\n`, `\f`, `\t`, `\r`, `\b`, `\v`) enclosed in single quotes `'`,

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

A string (**T_STRING**) is a sequence of zero or more printable ASCII characters enclosed within double quotes `"`.

> [!NOTE]
> For the time being, the language only supports single-line strings, so there is no way to signal that a string continues on to the next line.

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

Comments in Simple C work in much the same way as in C. The language ignores everything written after the `//` character until the end of the current line. Multi-line comments are enclosed in `/*` and `*/`.

## Grammar

The grammar of the C programming language is described by the subsequent set of rules.

- **program** → declarations functions main_function | declarations main_function | functions main_function | main_function ;

- **declarations** → declarations declaration | declaration ;

- **declaration** → basic_type names T_SEMI ;

- **basic_type** → T_INT | T_CHAR | T_FLOAT | T_DOUBLE ;

- **names** → names T_COMMA var_init | var_init ;

- **var_init** → variable init ;

- **variable** → T_ID ;

- **init** →  T_ASSIGN constant | ε ;

- **constant** → T_ICONST | T_FCONST | T_CCONST ;

- **functions** → functions function | function ;

- **function** → function_head function_tail ;

- **function_head** → function_head_start parameters T_RPAREN | function_head_start T_RPAREN ;

- **function_head_start** → basic_type T_ID T_LPAREN | T_VOID T_ID T_LPAREN ;

- **parameters** → parameters T_COMMA parameter | parameter ;

- **parameter** → basic_type T_ID ;

- **function_tail** → T_LBRACE declarations statements T_RBRACE | T_LBRACE statements T_RBRACE;

- **statements** → statements statement | statement ;

- **statement** → if_statement | for_statement | while_statement | assignment T_SEMI | T_CONTINUE T_SEMI | T_BREAK T_SEMI | function_call T_SEMI | var_ref T_INCDEC T_SEMI | T_INCDEC var_ref T_SEMI | print_statement | input_statement | return_statement ;

- **if_statement** → T_IF T_LPAREN expression T_RPAREN tail else_if optional_else | T_IF T_LPAREN expression T_RPAREN tail optional_else ;

- **expression** → expression T_ADDOP expression | expression T_MULOP expression | var_ref T_INCDEC | T_INCDEC var_ref | expression T_OROP expression | expression T_ANDOP expression | T_NOTOP expression | expression T_EQUOP expression | expression T_RELOP expression | T_PAREN expression T_RPAREN | var_ref | constant | T_ADDOP constant | function_call ;

- **var_ref** → variable ;

- **function_call** → variable T_LPAREN arguments T_RPAREN | variable T_LPAREN T_RPAREN ;

- **arguments** → arguments T_COMMA argument | argument ;

- **argument** → var_ref | constant | T_ADDOP constant ;

- **tail** → T_LBRACE statements T_RBRACE ;

- **else_if** → else_if T_ELSE T_IF T_LPAREN expression T_RPAREN tail | T_ELSE T_IF T_LPAREN expression T_RPAREN tail ;

- **optional_else** → T_ELSE tail | ε;

- **for_statement** → T_FOR T_LPAREN assignment T_SEMI expression T_SEMI var_ref T_INCDEC T_RPAREN tail ;

- **assignment** → var_ref T_ASSIGN expression ;

- **while_statement** → T_WHILE T_LPAREN expression T_RPAREN tail ;

- **print_statement** → T_PRINT expression T_SEMI | T_PRINT T_STRING T_SEMI ;

- **input_statement** → T_INPUT var_ref T_SEMI ;

- **return_statement** → T_RETURN expression T_SEMI | T_RETURN T_SEMI ;

- **main_function** → main_head function_tail ;

- **main_head** → T_INT T_MAIN T_LPAREN T_RPAREN ;

> [!NOTE]
> The `|` symbol separates the right-hand sides of the rules, and `ε` is the empty string.

The grammar is ambiguous, but with appropriate transformations or auxiliary descriptions of operator precedence and associativity, it can be made unambiguous.

The start symbol of the grammar is `program`.

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

The semantics of the Simple C programming language are determined by a set of rules governing the structure of a valid program. Some of these rules are likely covered by the language’s syntax itself, or by auxiliary descriptions that make it unambiguous. All remaining rules must be incorporated into the compiler itself using semantic functions that are executed during the conversion of a program into intermediate code (an abstract syntax tree).

### Data Types

Simple C supports four basic data types:

- `int` type → for integer numbers
- `float` type → for single precision floating-point numbers
- `double` type → for double precision floating-point numbers
- `char` type → for character types

#### Type size

The size and representation of the arithmetic data types (`int`, `float`, `double`) is dependent on the target architecture. Conversely, the character type (`char`), takes up a single byte and is represented in ASCII encoding.

#### Incomplete `void` type

The language also includes the special type `void`, which is used for incomplete types. This type is intended solely for use with function return values when a function does not return anything.

#### Strings

Although the language includes strings (**T_STRING**), these are only used within the `print` statement. As such, there is no separate string type.

#### Derived Types

The language is simplified to the extent that it does not include arrays, structures, unions, pointers or enumerations.

> [!NOTE]
> It is possible that the language may be extended in the future.

#### Type compatibility

|   Type   |                 Type Promotion                | 
| :------: | :-------------------------------------------: |
| `int`    | Can be promoted to `float` or `double`        |
| `float`  | Can be promoted to `double`                   |
| `double` | Stays as `double`                             | 
| `char`   | Can be promoted to `int`, `float` or `double` | 
| `void`   | Cannot be promoted                            | 

### Variable Declarations

Variables are declared with a specific type and an identifier (ID) that represents them. It is possible to declare multiple variables of the same type within a single declaration, provided that the identifiers are separated by commas.

> [!IMPORTANT]
> A variable or function parameter cannot be of type `void`.

<details>
    <summary><b>Examples</b></summary>

```c
int a;          /* declaration of one variable */
float b, c;     /* declaration of two variables of same type */
```

</details>

#### Scope Types

- `GLOBAL` scope → for global variables and function identifiers which are universally accessible throughout the program.
- `LOCAL` scope → for parameters and variables that are declared within functions and are only accessible within the functions in which they are declared.

#### Variable redeclarations

Unlike in C, the Simple C language does not allow variables to be redeclared within a nested scope. Therefore, if an identifier name has already been used for a global variable, it cannot be used again for a variable or parameter declaration within a function scope. This doesn't mean that redeclaration is entirely prohibited in this language. The only case in which redeclaration is allowed is for identifiers with the same name declared in distinct scopes. In the context of Simple C, this means that only different functions can have variables or parameters with the same identifier.

<details>
    <summary><b>Valid Example</b></summary>

```c
void foo1(){
    int i;      /* local variable declaration */
}
void foo2(){
    int i;      /* local variable declaration */
}
int main(){
    int i;      /* local variable declaration */
    ... 
}
```

</details>

<details>
    <summary><b>Invalid Example</b></summary>

```c
int i;          /* global variable declaration */
int main(){
    int i;      /* redeclaration of global variable prohibited in Simple C */
    ... 
}
```

</details>

#### Undeclared variables

The Simple C language strictly prohibits the use of a variable that has not been declared beforehand.

### Variable Initializations

Variables may be initialized when they are declared by assigning a constant value to them. If a declaration contains more than one variable, it is possible to assign an initial value to some of them and leave the rest with the default value.

> [!IMPORTANT]
> The initialization value must be of the same or a compatible type.

<details>
    <summary><b>Examples</b></summary>

```c
int i = 0;                  /* initialization of same type */
char c1, c2 = 'u', c3;      /* Initialization is only done for one of them, and its value is of the same type */
float f = 0;                /* initialization of compatible type */
```

</details>

### Function Declarations

Functions are declared with a specific return type and an identifier (ID) that represents the function. The return type may be one of the basic types, or it be `void` if the function doesn't return anything. Optional parameters can be included in parentheses. A parameter is a pair consisting of a type and an identifier, separated by commas. Variable declarations and statements are enclosed in curly braces.

<details>
    <summary><b>Examples</b></summary>

```c
int add(int a, int b) {     /* function with two parameters */
    ...
}
void foo() {                /* function without parameters */

}
```

</details>

### Expressions

An expression may contain binary operations (arithmetic, logical, equality, relational), unary operations (increment/decrement, logical NOT, unary minus on constants), parenthesised sub‑expressions, variable references, constants, and non-void function calls.

<details>
    <summary><b>Examples</b></summary>

```c
a               /* variable reference */
5 * a + 1       /* arithmetic expression */
c == d          /* equality expression */
i < 10          /* relational expression */
i++             /* unary operation */
!(a && b)       /* logical expresssion */
-5              /* unary operation */
3.14            /* constant */
add(a, 3)       /* function call */
```

</details>

### Precedencies and Associativities

|          Operator         |                        Description                        | Associativity |
| :-----------------------: | :-------------------------------------------------------: | :-----------: |
| `,`                       | Comma                                                     | Left-to-right |
| `=`                       | Assignment                                                | Right-to-left |
| `\|\|`                    | Logical OR                                                | Left-to-right |
| `&&`                      | Logical AND                                               | Left-to-right |
| `==`, `!=`                | Equality/Inequality operators                             | Left-to-right |
| `<`, `<=`, `>`, `>=`      | Relational operators                                      | Left-to-right |
| `+`, `-`                  | Addition and subtraction                                  | Left-to-right |
| `*`, `/`, `%`             | Multiplication, division and remainder                    | Left-to-right |
| `!`, `++`, `--`, `+`, `-` | Logical NOT, prefix increment/decrement, unary plus/minus | Right-to-left |
| `()`, `++`, `--`          | Function call, postfix increment/decrement                | Left-to-right |

> [!NOTE]
> The above table is arranged in ascending order of precedence, in line with how operator precedence is declared in Bison or Yacc.

### Statements

 In this language, a statement can be one of the following: a conditional, a loop, an assignment, a control-flow keyword (continue/break), a function call, a return statement, a print or input statement, or an increment/decrement operation. Most of the above are terminated with a semicolon (`;`), except for control structures that contain nested statements within bracelets (`{}`).

<details>
    <summary><b>Examples</b></summary>

```c
if (i < 5) {                /* if statement */
    ...
}
else {                      /* else branch */
    ...
}
for (i = 0; i < 5; i++) {   /* for loop */
    ...
    if (i == 3) {           /* if statement */
        continue;           /* continue statement */
    }
}
while (i > 0) {             /* while loop */
    ...
    if (i == 8) {           /* if statement */
        break;              /* break statement */
    }
    ...
}
k = 5 * func1(p) - a;       /* assignment */
i++:                        /* increment operation */
print "Message";            /* print statement */
print i + 1;                /* print statement */
input var;                  /* input statement */
return 0;                   /* return statement */
```

</details>