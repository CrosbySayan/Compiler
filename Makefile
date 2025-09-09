# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Executables to build
TARGETS = tokenizer parser

# Default target
all: $(TARGETS)

# Build tokenizer
tokenizer: tokenizer.o
	$(CC) $(CFLAGS) -o $@ $^

# Build parser 
parser: parser.o 
	$(CC) $(CFLAGS) -o $@ $^

# Compile tokenizer.c to tokenizer.o
tokenizer.o: tokenizer.c types.h
	$(CC) $(CFLAGS) -c tokenizer.c -o tokenizer.o

# Compile parser
parser.o: parser.c types.h
	$(CC) $(CFLAGS) -c parser.c -o parser.o

# Clean build files
clean:
	rm -f *.o $(TARGETS)

