# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -I./include

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = .

# Source files
SRCS = $(SRC_DIR)/tokenizer.c $(SRC_DIR)/parser.c $(SRC_DIR)/types.c $(SRC_DIR)/compiler.c
MAIN_SRC = main.c

# Object files
OBJS = compiler.o tokenizer.o parser.o types.o main.o

# Executables to build
TARGETS = tokenizer parser main compiler

# Default target
all: $(TARGETS)


# Build compiler executable (used for testing actual compiler)
compiler: compiler.o tokenizer.o parser.o types.o
	$(CC) $(CFLAGS) -o $@ $^

# Build main executable (combines all modules)
main: main.o tokenizer.o parser.o types.o
	$(CC) $(CFLAGS) -o $@ $^

# Build tokenizer standalone
tokenizer: tokenizer.o types.o
	$(CC) $(CFLAGS) -o $@ $^

# Build parser standalone
parser: parser.o types.o
	$(CC) $(CFLAGS) -o $@ $^

# Compile compiler
compiler.o: $(SRC_DIR)/compiler.c $(INCLUDE_DIR)/types.h $(INCLUDE_DIR)/tokenizer.h $(INCLUDE_DIR)/parser.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/compiler.c -o compiler.o

# Compile main.c (in root directory)
main.o: main.c $(INCLUDE_DIR)/types.h $(INCLUDE_DIR)/tokenizer.h $(INCLUDE_DIR)/parser.h
	$(CC) $(CFLAGS) -c main.c -o main.o

# Compile types.c
types.o: $(SRC_DIR)/types.c $(INCLUDE_DIR)/types.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/types.c -o types.o

# Compile tokenizer.c
tokenizer.o: $(SRC_DIR)/tokenizer.c $(INCLUDE_DIR)/tokenizer.h $(INCLUDE_DIR)/types.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/tokenizer.c -o tokenizer.o

# Compile parser.c
parser.o: $(SRC_DIR)/parser.c $(INCLUDE_DIR)/parser.h $(INCLUDE_DIR)/tokenizer.h $(INCLUDE_DIR)/types.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/parser.c -o parser.o

# Clean build files
clean:
	rm -f *.o $(TARGETS)

# Phony targets
.PHONY: all clean
