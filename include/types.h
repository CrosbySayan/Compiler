#ifndef TYPE_H
#define TYPE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    // Single Symbols
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACK,
    RIGHT_BRACK,
    SEMI,

    IDEN,   // "main"
    ASIGN,  // =
    LITERAL,
    RET,
    INT,
    ILLEGAL,  // Unknown characters
} TokenType;

typedef struct Token {
    TokenType type;       // Type of token
    char *token_literal;  // The literal character in the token

} Token;

typedef struct TokenNode {
    Token token;
    struct TokenNode *next;
} TokenNode;

typedef struct {
    TokenNode *head;
    TokenNode *tail;
} TokenList;

// Create a new token once a REGEX break happens
Token create_token(TokenType type, const char *literal);

// Initialize an empty token list
void init_token_list(TokenList *list);

// Add token to the end of the list
void add_token(TokenList *list, struct Token token);

// Pops the first token from the head of the list
TokenNode *pop_token(TokenList *list);

// Free memory of given token
void free_token(TokenNode *tok);

// Free all memory used by the list
void free_token_list(TokenList *list);

// Debug: Print your list of tokens
void print_token_list(const TokenList *list);

#endif
