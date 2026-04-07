# Simple Example

## Simple C Program Example

```c
int main() {
    int i;
    double val = 2.5;
    for (i = 0; i < 10; i++) {
        val = val * i + i;
    }
    print val;
    return 0;
}
```

## Intermediate Code Representation

```x86asm
main:
declare i
declare val
val = 2.500000
i = 0
_L0:
_tmp0 = i < 10
jumpifz _L2, _tmp0
_tmp1 = val * i
_tmp2 = _tmp1 + i
val = _tmp2
_L1:
i++
jump _L0
_L2:
print val
retv 0
```

## Debugging Information

<details>
    <summary><b>Console output</b></summary>

```
Inserted 'main' for the first time with line no. 1!
Entering scope 'main'
Inserted 'i' for the first time with line no. 2!
Inserted 'val' for the first time with line no. 3!
Found 'i' again at line no. 4!
Found 'i' again at line no. 4!
Found 'i' again at line no. 4!
Found 'val' again at line no. 5!
Found 'val' again at line no. 5!
Found 'i' again at line no. 5!
Found 'i' again at line no. 5!
Found 'val' again at line no. 7!
Hiding scope 'main'
Parsing finished!
Starting semantic analysis of program...
No redeclaration of identifier 'main' at line no. 1
Entering scope 'main'
No redeclaration of identifier 'i' at line no. 2
Set type of variable 'i' to 'int'
Declaration of variable 'i' of type 'int' has no initialization value
No redeclaration of identifier 'val' at line no. 3
Set type of variable 'val' to 'double'
Declaration of variable 'val' of type 'double' has initialization value of same type
Semantic analysis of assignment node at line no. 4
Reference of variable 'i' at line no. 4 is in scope 'main'
Variable 'i' declared at line no. 2 is correctly used in line no. 4
Constant Node of data type 'int' used in line no. 4. No semantic analysis necessary!
LHS data type is 'int'
RHS data type is 'int'
Types are the same!
Reference of variable 'i' at line no. 4 is in scope 'main'
Variable 'i' declared at line no. 2 is correctly used in line no. 4
Constant Node of data type 'int' used in line no. 4. No semantic analysis necessary!
Result data type of binary expression of operator type 'less' at line no. 4 is 'int'
Reference of variable 'i' at line no. 4 is in scope 'main'
Variable 'i' declared at line no. 2 is correctly used in line no. 4
Result data type of unary expression of operator type 'post_inc' at line no. 6 is 'int'
Semantic analysis of assignment node at line no. 5
Reference of variable 'val' at line no. 5 is in scope 'main'
Variable 'val' declared at line no. 3 is correctly used in line no. 5
Reference of variable 'val' at line no. 5 is in scope 'main'
Variable 'val' declared at line no. 3 is correctly used in line no. 5
Reference of variable 'i' at line no. 5 is in scope 'main'
Variable 'i' declared at line no. 2 is correctly used in line no. 5
Result data type of binary expression of operator type 'mul' at line no. 5 is 'double'
Reference of variable 'i' at line no. 5 is in scope 'main'
Variable 'i' declared at line no. 2 is correctly used in line no. 5
Result data type of binary expression of operator type 'add' at line no. 5 is 'double'
LHS data type is 'double'
RHS data type is 'double'
Types are the same!
Print statement node of type 'expression'
Reference of variable 'val' at line no. 7 is in scope 'main'
Variable 'val' declared at line no. 3 is correctly used in line no. 7
The data type of the output value is: 'double'
Set return type of return statement in line no. 8 to 'int'
Constant Node of data type 'int' used in line no. 8. No semantic analysis necessary!
Return statement data type is 'int'
Function return type is 'int'
Return statement of same type as function return value
Return statement was located at the of function 'main' of type 'int' as required!
Hiding scope 'main'
Entering scope 'main'
Entering context with node of kind 'for_loop'
Inserted '_tmp0' for the first time with line no. 4!
Inserted '_tmp1' for the first time with line no. 5!
Inserted '_tmp2' for the first time with line no. 5!
Hiding context with kind 'in_for_loop'
Hiding scope 'main'
Dumping symbol table to file...
Entering scope 'main'
Entering scope '_GLOBAL'
Dumping abstract syntax tree to JSON file...
```

</details>

<details>
    <summary><b>Lexer dump file</b></summary>

```
T_INT T_MAIN T_LPAREN T_RPAREN T_LBRACE
    T_INT T_ID T_SEMI
    T_DOUBLE T_ID T_ASSIGN T_FCONST T_SEMI
    T_FOR  T_LPARENT_ID T_ASSIGN T_ICONST T_SEMI T_ID T_RELOP T_ICONST T_SEMI T_IDT_INCDEC T_RPAREN T_LBRACE
        T_ID T_ASSIGN T_ID T_ADDOP T_ID T_ADDOP T_ID T_SEMI
    T_RBRACE
    T_PRINT T_ID T_SEMI
    T_RETURN T_ICONST T_SEMI
T_RBRACE
```

</details>

<details>
    <summary><b>Symbol table dump file</b></summary>

```c
------------ -------------- -------------- ------------ ------------
Name         Kind           Type           Scope        Line Numbers
------------ -------------- -------------- ------------ ------------
_tmp0        temporary      int            main            4 
_tmp1        temporary      double         main            5 
_tmp2        temporary      double         main            5 
i            variable       int            main            2    4    4    4    5    5 
val          variable       double         main            3    5    5    7 
main         function       int            _GLOBAL         1 
```

</details>

<details>
    <summary><b>Abstract syntax tree (AST) in JSON format</b></summary>

```json
{
    "kind": "program",
    "lineno": 1,
    "declarations": [],
    "functions": [],
    "main_function": {
        "kind": "function",
        "lineno": 1,
        "entry": {
            "kind": "function",
            "id": "main",
            "len": 4,
            "scope": {
                "parent": null,
                "kind": "global",
                "id": "_GLOBAL",
                "visibility": "visible"
            },
            "lines": [
                1
            ],
            "next": null,
            "ret_type": "int",
            "parameters": []
        },
        "function_tail": {
            "kind": "function_tail",
            "lineno": 2,
            "declarations": [
                {
                    "kind": "declaration",
                    "lineno": 2,
                    "d_type": "int",
                    "names": [
                        {
                            "kind": "variable",
                            "id": "i",
                            "len": 1,
                            "scope": {
                                "parent": {
                                    "parent": null,
                                    "kind": "global",
                                    "id": "_GLOBAL",
                                    "visibility": "visible"
                                },
                                "kind": "local",
                                "id": "main",
                                "visibility": "hidden"
                            },
                            "lines": [
                                2,
                                4,
                                4,
                                4,
                                5,
                                5
                            ],
                            "next": null,
                            "d_type": "int",
                            "init_value": {
                                "d_type": "undef",
                                "val": null
                            }
                        }
                    ]
                },
                {
                    "kind": "declaration",
                    "lineno": 3,
                    "d_type": "double",
                    "names": [
                        {
                            "kind": "variable",
                            "id": "val",
                            "len": 3,
                            "scope": {
                                "parent": {
                                    "parent": null,
                                    "kind": "global",
                                    "id": "_GLOBAL",
                                    "visibility": "visible"
                                },
                                "kind": "local",
                                "id": "main",
                                "visibility": "hidden"
                            },
                            "lines": [
                                3,
                                5,
                                5,
                                7
                            ],
                            "next": null,
                            "d_type": "double",
                            "init_value": {
                                "d_type": "double",
                                "val": 2.5
                            }
                        }
                    ]
                }
            ],
            "statements": [
                {
                    "kind": "for_loop",
                    "lineno": 4,
                    "initialize": {
                        "kind": "assignment",
                        "lineno": 4,
                        "variable_reference": {
                            "kind": "variable_reference",
                            "lineno": 4,
                            "entry": {
                                "kind": "variable",
                                "id": "i",
                                "len": 1,
                                "scope": {
                                    "parent": {
                                        "parent": null,
                                        "kind": "global",
                                        "id": "_GLOBAL",
                                        "visibility": "visible"
                                    },
                                    "kind": "local",
                                    "id": "main",
                                    "visibility": "hidden"
                                },
                                "lines": [
                                    2,
                                    4,
                                    4,
                                    4,
                                    5,
                                    5
                                ],
                                "next": null,
                                "d_type": "int",
                                "init_value": {
                                    "d_type": "undef",
                                    "val": null
                                }
                            }
                        },
                        "expression": {
                            "kind": "constant",
                            "lineno": 4,
                            "d_type": "int",
                            "val": 0
                        }
                    },
                    "condition": {
                        "kind": "expression_binary",
                        "lineno": 4,
                        "left": {
                            "kind": "variable_reference",
                            "lineno": 4,
                            "entry": {
                                "kind": "variable",
                                "id": "i",
                                "len": 1,
                                "scope": {
                                    "parent": {
                                        "parent": null,
                                        "kind": "global",
                                        "id": "_GLOBAL",
                                        "visibility": "visible"
                                    },
                                    "kind": "local",
                                    "id": "main",
                                    "visibility": "hidden"
                                },
                                "lines": [
                                    2,
                                    4,
                                    4,
                                    4,
                                    5,
                                    5
                                ],
                                "next": null,
                                "d_type": "int",
                                "init_value": {
                                    "d_type": "undef",
                                    "val": null
                                }
                            }
                        },
                        "op_type": "less",
                        "right": {
                            "kind": "constant",
                            "lineno": 4,
                            "d_type": "int",
                            "val": 10
                        },
                        "d_type": "int"
                    },
                    "increment": {
                        "kind": "expression_unary",
                        "lineno": 6,
                        "operand": {
                            "kind": "variable_reference",
                            "lineno": 4,
                            "entry": {
                                "kind": "variable",
                                "id": "i",
                                "len": 1,
                                "scope": {
                                    "parent": {
                                        "parent": null,
                                        "kind": "global",
                                        "id": "_GLOBAL",
                                        "visibility": "visible"
                                    },
                                    "kind": "local",
                                    "id": "main",
                                    "visibility": "hidden"
                                },
                                "lines": [
                                    2,
                                    4,
                                    4,
                                    4,
                                    5,
                                    5
                                ],
                                "next": null,
                                "d_type": "int",
                                "init_value": {
                                    "d_type": "undef",
                                    "val": null
                                }
                            }
                        },
                        "op_type": "post_inc",
                        "d_type": "int"
                    },
                    "for_branch": [
                        {
                            "kind": "assignment",
                            "lineno": 5,
                            "variable_reference": {
                                "kind": "variable_reference",
                                "lineno": 5,
                                "entry": {
                                    "kind": "variable",
                                    "id": "val",
                                    "len": 3,
                                    "scope": {
                                        "parent": {
                                            "parent": null,
                                            "kind": "global",
                                            "id": "_GLOBAL",
                                            "visibility": "visible"
                                        },
                                        "kind": "local",
                                        "id": "main",
                                        "visibility": "hidden"
                                    },
                                    "lines": [
                                        3,
                                        5,
                                        5,
                                        7
                                    ],
                                    "next": null,
                                    "d_type": "double",
                                    "init_value": {
                                        "d_type": "double",
                                        "val": 2.5
                                    }
                                }
                            },
                            "expression": {
                                "kind": "expression_binary",
                                "lineno": 5,
                                "left": {
                                    "kind": "expression_binary",
                                    "lineno": 5,
                                    "left": {
                                        "kind": "variable_reference",
                                        "lineno": 5,
                                        "entry": {
                                            "kind": "variable",
                                            "id": "val",
                                            "len": 3,
                                            "scope": {
                                                "parent": {
                                                    "parent": null,
                                                    "kind": "global",
                                                    "id": "_GLOBAL",
                                                    "visibility": "visible"
                                                },
                                                "kind": "local",
                                                "id": "main",
                                                "visibility": "hidden"
                                            },
                                            "lines": [
                                                3,
                                                5,
                                                5,
                                                7
                                            ],
                                            "next": null,
                                            "d_type": "double",
                                            "init_value": {
                                                "d_type": "double",
                                                "val": 2.5
                                            }
                                        }
                                    },
                                    "op_type": "mul",
                                    "right": {
                                        "kind": "variable_reference",
                                        "lineno": 5,
                                        "entry": {
                                            "kind": "variable",
                                            "id": "i",
                                            "len": 1,
                                            "scope": {
                                                "parent": {
                                                    "parent": null,
                                                    "kind": "global",
                                                    "id": "_GLOBAL",
                                                    "visibility": "visible"
                                                },
                                                "kind": "local",
                                                "id": "main",
                                                "visibility": "hidden"
                                            },
                                            "lines": [
                                                2,
                                                4,
                                                4,
                                                4,
                                                5,
                                                5
                                            ],
                                            "next": null,
                                            "d_type": "int",
                                            "init_value": {
                                                "d_type": "undef",
                                                "val": null
                                            }
                                        }
                                    },
                                    "d_type": "double"
                                },
                                "op_type": "add",
                                "right": {
                                    "kind": "variable_reference",
                                    "lineno": 5,
                                    "entry": {
                                        "kind": "variable",
                                        "id": "i",
                                        "len": 1,
                                        "scope": {
                                            "parent": {
                                                "parent": null,
                                                "kind": "global",
                                                "id": "_GLOBAL",
                                                "visibility": "visible"
                                            },
                                            "kind": "local",
                                            "id": "main",
                                            "visibility": "hidden"
                                        },
                                        "lines": [
                                            2,
                                            4,
                                            4,
                                            4,
                                            5,
                                            5
                                        ],
                                        "next": null,
                                        "d_type": "int",
                                        "init_value": {
                                            "d_type": "undef",
                                            "val": null
                                        }
                                    }
                                },
                                "d_type": "double"
                            }
                        }
                    ],
                    "label_start": "_L0",
                    "label_increment": "_L1",
                    "label_end": "_L2"
                },
                {
                    "kind": "print_statement",
                    "lineno": 7,
                    "p_type": "expression",
                    "print_value": {
                        "kind": "variable_reference",
                        "lineno": 7,
                        "entry": {
                            "kind": "variable",
                            "id": "val",
                            "len": 3,
                            "scope": {
                                "parent": {
                                    "parent": null,
                                    "kind": "global",
                                    "id": "_GLOBAL",
                                    "visibility": "visible"
                                },
                                "kind": "local",
                                "id": "main",
                                "visibility": "hidden"
                            },
                            "lines": [
                                3,
                                5,
                                5,
                                7
                            ],
                            "next": null,
                            "d_type": "double",
                            "init_value": {
                                "d_type": "double",
                                "val": 2.5
                            }
                        }
                    }
                },
                {
                    "kind": "return_statement",
                    "lineno": 8,
                    "ret_type": "int",
                    "expression": {
                        "kind": "constant",
                        "lineno": 8,
                        "d_type": "int",
                        "val": 0
                    }
                }
            ]
        }
    }
}
```

</details>