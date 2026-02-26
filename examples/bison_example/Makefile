CC := gcc
CFLAGS = -g -Wall -Wextra -std=c11

YACC := bison

YACC_SRC := calc.y
YACC_OUT := calc.tab.c

TARGET := calc

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(YACC_OUT)
	@$(CC) $(CFLAGS) -o $@ $(YACC_OUT)

$(YACC_OUT): $(YACC_SRC)
	@$(YACC) -o $@ $<

clean:
	@rm $(TARGET) $(YACC_OUT)

run:
	@./$(TARGET)
