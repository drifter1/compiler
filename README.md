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
-Function Semantics (part 1) -> ...

What remains now is:  
-Semantic analysis which includes creating and using even more semantic rules and making the attribute grammar
-Intermediate code generation in form of a Abstract syntax tree  
-Final machine code generation in MIPS Assembly

After doing all that we could also get into Optimizations, Extensions and even more if you like :)
