# compiler

![Compiler Design Steps](https://i.ibb.co/Y7rChXr/compiler-series.png)

A short Description of this repository:  
It contains all the Code from my "Writing a simple Compiler on my own" series on Steemit (step by step / article by article), where I am implementing a complete Compiler for a simple C-like Language using the C-tools Flex and Bison and self-written Custom Structures and Code.


# Articles
It's worth noting that not all articles contain actual Code. Compiler design in general is mostly about understanding how everything needs to work. After understanding the basic principle, the implementation is much easier, which is why some articles are more or less 90% theory!

Until now we covered the following...  
## General Knowledge and Lexical Analysis
- **Compiler design in general (introduction)** -> https://steemit.com/programming/@drifter1/writing-a-simple-compiler-on-my-own-introduction 
- **The simple C-like Language** -> https://steemit.com/programming/@drifter1/writing-a-simple-compiler-on-my-own-a-simple-c-language  
- **Lexical Analysis and the implementation of a simple Lexer using Flex** -> https://steemit.com/programming/@drifter1/writing-a-simple-compiler-on-my-own-lexical-analysis-using-flex  
- **The basic implementation/structure of a Symbol Table** -> https://steemit.com/programming/@drifter1/writing-a-simple-compiler-on-my-own-symbol-table-basic-structure  
- **Using the Symbol Table in the Lexer** -> https://steemit.com/programming/@drifter1/writing-a-simple-compiler-on-my-own-using-symbol-tables-in-the-lexer

## Syntax Analysis
- **Syntax Analysis Theory needed**-> https://steemit.com/programming/@drifter1/writing-a-simple-compiler-on-my-own-syntax-analysis-theory  
- **Bison tool basics / tutorial** -> https://steemit.com/programming/@drifter1/writing-a-simple-compiler-on-my-own-bison-basics  
- **Creating a Grammar for the Language by also implementing a first Parser** -> https://steemit.com/programming/@drifter1/writing-a-simple-compiler-on-my-own-creating-a-grammar-for-our-language  
- **Combining Flex and Bison** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-combine-flex-and-bison  
- **Passing information from the Lexer to the Parser** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-passing-information-from-lexer-to-parser  
- **Finishing Off the Grammar/Parser (part 1)** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-finishing-off-the-grammer-parser-part-1  
- **Finishing Off the Grammar/Parser (part 2)** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-finishing-off-the-grammar-parser-part-2-c-flex-bison

## Semantic Analysis (1)
- **Semantic Analysis Theory** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-semantic-analysis-theory-c-flex-bison  
- **Semantics Examples** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-semantics-examples-c-flex-bison  
- **Scope Resolution using Symbol Table** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own---scope-resolution-using-the-symbol-table-cflexbison  
- **Type Declaration and Checking** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-type-declaration-and-checking-c-flex-bison  
- **Function Semantics (part 1)** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-function-semantics-part-1-c-flex-bison  
- **Function Semantics (part 2)** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-function-semantics-part-2-c-flex-bison

## Intermediate Code Generation (AST)
- **Abstract Syntax Tree Principle** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-abstract-syntax-tree-principle-c-flex-bison  
- **Abstract Syntax Tree Structure** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-abstract-syntax-tree-structure-c-flex-bison  
- **Abstract Syntax Tree Management** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-abstract-syntax-tree-management-c-flex-bison  
- **Action Rules for Declarations and Initializations** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-action-rules-for-declarations-and-initializations-c-flex-bison  
- **Action Rules for Expressions** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-action-rules-for-expressions-c-flex-bison  
- **Action Rules for Assignments and Simple Statements** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-action-rules-for-assignments-and-simple-statements-c-flex-bison  
- **Action Rules for If-Else Statements** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-action-rules-for-if-else-statements-c-flex-bison  
- **Action Rules for Loop Statements and some Fixes** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-action-rules-for-loop-statements-and-some-fixes-c-flex-bison  
- **Action Rules for Function Declarations (part 1)** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-action-rules-for-function-declarations-part-1-c-flex-bison  
- **Action Rules for Function Declarations (part 2)** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-action-rules-for-function-declarations-part-2-c-flex-bison  
- **Action Rules for Function Calls** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-action-rules-for-function-calls-c-flex-bison

## Semantic Analysis (2)
- **Datatype attribute for Expressions** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-datatype-attribute-for-expressions-c-flex-bison  
- **Type Checking for Assignments** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-type-checking-for-assignments-c-flex-bison  
- **Revisit Queue and Parameter Checking (part 1)** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-revisit-queue-and-parameter-checking-part-1-c-flex-bison  
- **Revisit Queue and Parameter Checking (part 2)** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-revisit-queue-and-parameter-checking-part-2-c-flex-bison  
- **Revisit Queue and Parameter Checking (part 3)** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-revisit-queue-and-parameter-checking-part-3-c-flex-bison  
- **Revisit Queue and Parameter Checking (part 4)** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-revisit-queue-and-parameter-checking-part-4-c-flex-bison  
- **Revisit Queue and Assignment Checking (part 1)** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-revisit-queue-and-assignment-checking-part-1-c-flex-bison  
- **Revisit Queue and Assignment Checking (part 2)** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-revisit-queue-and-assignment-checking-part-2-c-flex-bison  
- **Revisit Queue and Assignment Checking (part 3)** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-revisit-queue-and-assignment-checking-part-3-c-flex-bison

## Machine Code Generation  
- **Machine Code Generation Principles** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-machine-code-generation-principles  
- **MIPS Instruction Set** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-mips-instruction-set  
- **Simple Examples in MIPS Assembly** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-simple-examples-in-mips-assembly  
- **full_example.c in MIPS Assembly (part 1)** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-fullexample-c-in-mips-assembly  
- **full_example.c in MIPS Assembly (part 2)** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-fullexample-c-in-mips-assembly-part-2  
- **Generating Code for Declarations and Initializations** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-generating-code-for-declarations-and-initializations  
- **Generating Code for Array Initializations and String Messages** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-generating-code-for-array-initializations-and-string-messages  
- **Register Allocation & Assignment Theory** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-register-allocation-and-assignment-theory  
- **Implementing Register Allocation (part 1)** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-implementing-register-allocation-part-1  
- **Implementing Register Allocation (part 2)** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-implementing-register-allocation-part-2  
- **Implementing Register Allocation (part 3)** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-implementing-register-allocation-part-3  
- **Implementing Register Allocation (part 4)** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-implementing-register-allocation-part-4  
- **Generating Code for Expressions (part 1)** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-generating-code-for-expressions-part-1  
- **Generating Code for Expressions (part 2)** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-generating-code-for-expressions-part-2  
- **Generating Code for Expressions (part 3)** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-generating-code-for-expressions-part-3  
- **Generating Code for Simple Statements** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-generating-code-for-simple-statements  
- **Generating Code for Assignments (part 1)** -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-generating-code-for-assignments-part-1

# Next Up
What remains now is:  
- Machine Code generation in MIPS Assembly (remaining cases)
- Various Optimizations in the Compiler's Code

After doing all that we could also get into Optimizations, Extensions and even more if you like :)
