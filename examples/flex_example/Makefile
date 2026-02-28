CC := gcc
CFLAGS = -g -Wall -Wextra -std=c11

LEX = flex

LEX_SRC := lexer.l
LEX_OUT := lex.yy.c

TARGET := lexer

EXAMPLE = example.code

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(LEX_OUT)
	@$(CC) $(CFLAGS) -o $@ $(LEX_OUT)

$(LEX_OUT): $(LEX_SRC)
	@$(LEX) -o $@ $<

clean:
	@rm $(TARGET) $(LEX_OUT)

run:
	@./$(TARGET) $(EXAMPLE)
