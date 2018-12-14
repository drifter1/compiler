# compiler
A short Description of this repository:  
It contains all the Code from my "Writing a simple Compiler on my own" series on Steemit (step by step / article by article), where we are implementing a complete Compiler for a simple C-like Language using the C-tools Flex and Bison.

It's worth noting that not all articles contain actual Code.  
Compiler design in general is mostly about understanding how everything needs to work.  
After understanding the basic principle, the implementation is much easier, which is why some articles are 90% theory!

Until now we covered:  
-Compiler design in general (introduction) -> https://steemit.com/programming/@drifter1/writing-a-simple-compiler-on-my-own-introduction  
-The simple C-like Language -> https://steemit.com/programming/@drifter1/writing-a-simple-compiler-on-my-own-a-simple-c-language  
-Lexical Analysis and the implementation of a simple Lexer using Flex -> https://steemit.com/programming/@drifter1/writing-a-simple-compiler-on-my-own-lexical-analysis-using-flex  
-The basic implementation/structure of a Symbol Table -> https://steemit.com/programming/@drifter1/writing-a-simple-compiler-on-my-own-symbol-table-basic-structure  
-Using the Symbol Table in the Lexer -> https://steemit.com/programming/@drifter1/writing-a-simple-compiler-on-my-own-using-symbol-tables-in-the-lexer  
-Syntax Analysis Theory needed-> https://steemit.com/programming/@drifter1/writing-a-simple-compiler-on-my-own-syntax-analysis-theory  
-Bison tool basics / tutorial -> https://steemit.com/programming/@drifter1/writing-a-simple-compiler-on-my-own-bison-basics  
-Creating a Grammar for the Language by also implementing a first Parser -> https://steemit.com/programming/@drifter1/writing-a-simple-compiler-on-my-own-creating-a-grammar-for-our-language  
-Combining Flex and Bison -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-combine-flex-and-bison  
-Passing information from the Lexer to the Parser -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-passing-information-from-lexer-to-parser  
-Finishing Off the Grammar/Parser (part 1) -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-finishing-off-the-grammer-parser-part-1  
-Finishing Off the Grammar/Parser (part 2) -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-finishing-off-the-grammar-parser-part-2-c-flex-bison  
-Semantic Analysis Theory -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-semantic-analysis-theory-c-flex-bison  
-Semantics Examples -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-semantics-examples-c-flex-bison  
-Scope Resolution using Symbol Table -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own---scope-resolution-using-the-symbol-table-cflexbison  
-Type Declaration and Checking -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-type-declaration-and-checking-c-flex-bison  
-Function Semantics (part 1) -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-function-semantics-part-1-c-flex-bison  
-Function Semantics (part 2) -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-function-semantics-part-2-c-flex-bison  
-Abstract Syntax Tree Principle -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-abstract-syntax-tree-principle-c-flex-bison  
-Abstract Syntax Tree Structure -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-abstract-syntax-tree-structure-c-flex-bison  
-Abstract Syntax Tree Management -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-abstract-syntax-tree-management-c-flex-bison  
-Action Rules for Declarations and Initializations -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-action-rules-for-declarations-and-initializations-c-flex-bison  
-Action Rules for Expressions -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-action-rules-for-expressions-c-flex-bison  
-Action Rules for Assignments and Simple Statements -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-action-rules-for-assignments-and-simple-statements-c-flex-bison  
-Action Rules for If-Else Statemenets -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-action-rules-for-if-else-statements-c-flex-bison  
-Action Rules for Loop Statements and some Fixes -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-action-rules-for-loop-statements-and-some-fixes-c-flex-bison  
-Action Rules for Function Declarations (part 1) -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-action-rules-for-function-declarations-part-1-c-flex-bison  
-Action Rules for Function Declarations (part 2) -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-action-rules-for-function-declarations-part-2-c-flex-bison  
-Action Rules for Function Calls -> https://steemit.com/utopian-io/@drifter1/writing-a-simple-compiler-on-my-own-action-rules-for-function-calls-c-flex-bison  
-Datatype attribute for Expressions ->

What remains now is:  
-Semantic analysis which includes creating and using even more semantic and so action rules in Bison  
-Final machine code generation in MIPS Assembly

After doing all that we could also get into Optimizations, Extensions and even more if you like :)
