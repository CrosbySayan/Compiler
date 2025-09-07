# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Executables
TARGETS = parser token-test

# Source files per target
PARSER_SRCS = parser.c tokenizer.c
TOKEN_TEST_SRCS = token-test.c tokenizer.c

# Object files per target
PARSER_OBJS = $(PARSER_SRCS:.c=.o)
TOKEN_TEST_OBJS = $(TOKEN_TEST_SRCS:.c=.o)

# Default target
all: $(TARGETS)

# Build parser
parser: $(PARSER_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Build token-test
token-test: $(TOKEN_TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .c to .o
%.o: %.c types.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f *.o $(TARGETS)
