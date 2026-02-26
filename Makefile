# compiler and flags
CC = gcc
CFLAGS = -g -Wall -Wextra -std=c11

# lexer and flags
LEX = flex
LFLAGS = 

# parser and flags
YACC = bison
YFLAGS = -d

# make directory
MKDIR_P = mkdir -p

# directories
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = build

# source files
LEX_SRC = $(SRC_DIR)/lexer.l
YACC_SRC = $(SRC_DIR)/parser.y
C_SRC = $(wildcard $(SRC_DIR)/*.c)

# lexer and parser outputs
LEX_OUT = $(OBJ_DIR)/lex.yy.c
YACC_OUT = $(OBJ_DIR)/parser.tab.c

# target file
TARGET = $(BIN_DIR)/compiler

# example directory and file
EXAMPLES_DIR = examples/simple_c_examples
EXAMPLE = $(EXAMPLES_DIR)/example1.c

.PHONY: all clean run clean-run

# Default target
all: $(TARGET)

$(TARGET): $(YACC_OUT) $(LEX_OUT) | $(BIN_DIR)
	@$(CC) $(CFLAGS) -o $@ $(YACC_OUT) $(LEX_OUT) $(C_SRC)

$(LEX_OUT): $(LEX_SRC) | $(OBJ_DIR)
	@$(LEX) $(LFLAGS) -o $@ $<

$(YACC_OUT): $(YACC_SRC) | $(OBJ_DIR)
	@$(YACC) $(YFLAGS) -o $@ $<

$(BIN_DIR):
	@$(MKDIR_P) $@

$(OBJ_DIR):
	@$(MKDIR_P) $@

# Clean build files
clean:
	@rm -rf $(BIN_DIR) $(OBJ_DIR)

# Run the program
run: $(TARGET)
	@./$< $(EXAMPLE)

# Clean run files
clean-run:
	@rm *.out
