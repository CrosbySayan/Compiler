# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Executables to build
TARGETS = tokenizer parser main

# Default target
all: $(TARGETS)

# Build main executable (combines all modules)
main: main.o tokenizer.o parser.o types.o
	$(CC) $(CFLAGS) -o $@ $^

# Build tokenizer standalone
tokenizer: tokenizer.o types.o
	$(CC) $(CFLAGS) -o $@ $^

# Build parser standalone
parser: parser.o types.o
	$(CC) $(CFLAGS) -o $@ $^

# Compile main.c
main.o: main.c types.h tokenizer.h parser.h
	$(CC) $(CFLAGS) -c main.c -o main.o

# Compile types.c (shared token functions)
types.o: types.c types.h
	$(CC) $(CFLAGS) -c types.c -o types.o

# Compile tokenizer.c
tokenizer.o: tokenizer.c tokenizer.h types.h
	$(CC) $(CFLAGS) -c tokenizer.c -o tokenizer.o

# Compile parser.c
parser.o: parser.c parser.h tokenizer.h types.h
	$(CC) $(CFLAGS) -c parser.c -o parser.o

# Clean build files
clean:
	rm -f *.o $(TARGETS)

# Phony targets
.PHONY: all clean
