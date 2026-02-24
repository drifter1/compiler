CC := gcc
LEX := flex
YACC := bison
MKDIR_P := mkdir -p

SRC_DIR := src
BIN_DIR := bin
OBJ_DIR := build

LEX_SRC := $(SRC_DIR)/lexer.l
YACC_SRC := $(SRC_DIR)/parser.y
C_SRC := $(wildcard $(SRC_DIR)/*.c)

LEX_OUT := $(OBJ_DIR)/lex.yy.c
YACC_OUT := $(OBJ_DIR)/parser.tab.c

TARGET := $(BIN_DIR)/compiler

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(YACC_OUT) $(LEX_OUT) | $(BIN_DIR)
	@$(CC) -o $@ $(YACC_OUT) $(LEX_OUT) $(C_SRC)

$(LEX_OUT): $(LEX_SRC) | $(OBJ_DIR)
	@$(LEX) -o $@ $<

$(YACC_OUT): $(YACC_SRC) | $(OBJ_DIR)
	@$(YACC) -o $@ -d $<

$(BIN_DIR):
	@$(MKDIR_P) $@

$(OBJ_DIR):
	@$(MKDIR_P) $@

clean:
	@rm -rf $(BIN_DIR) $(OBJ_DIR)
