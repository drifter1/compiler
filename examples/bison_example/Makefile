CC := gcc
YACC := bison

YACC_SRC := calc.y
YACC_OUT := calc.tab.c
TARGET := calc

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(YACC_OUT)
	@$(CC) -o $@ $(YACC_OUT)

$(YACC_OUT): $(YACC_SRC)
	@$(YACC) -o $@ $<

clean:
	@rm $(TARGET) $(YACC_OUT)
