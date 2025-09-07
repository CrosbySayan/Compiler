# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Executable names
TARGETS = tokenizer parser

# Source files
TOKENIZER_SRCS = tokenizer.c
PARSER_SRCS = parser.c

# Object files
TOKENIZER_OBJS = $(TOKENIZER_SRCS:.c=.o)
PARSER_OBJS = $(PARSER_SRCS:.c=.o)

# Default target
all: $(TARGETS)

# Build tokenizer
tokenizer: $(TOKENIZER_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Build parser
parser: $(PARSER_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .c into .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f *.o $(TARGETS)
