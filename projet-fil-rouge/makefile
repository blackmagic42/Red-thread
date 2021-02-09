EXEC=main
CFLAGS=-lm
SRC=$(wildcard *.c)

all:PYTHON

PYTHON:
	@echo "launching python program..."
	@python3.8 process.py

PROGRAM: $(SRC)
	@echo "compiling c files..."
	@gcc $^ -o $(EXEC) $(CFLAGS)
	@echo "starting generation..."
	@./$(EXEC)
	
