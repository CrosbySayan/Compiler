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
    RET,
    INT,
    ILLEGAL,  // Unknown characters
} TokenType;

typedef struct Token {
    TokenType type;       // Type of token
    char* token_literal;  // The literal character in the token

} Token;

typedef struct TokenNode {
    Token token;
    struct TokenNode* next;
} TokenNode;

typedef struct {
    TokenNode* head;
    TokenNode* tail;
} TokenList;

// Create a new token once a REGEX break happens
Token create_token(TokenType type, const char* literal) {
    struct Token t;
    t.type = type;
    t.token_literal = strdup(literal);
    return t;
}

// Initialize an empty token list
void init_token_list(TokenList* list) {
    list->head = NULL;
    list->tail = NULL;
}

// Add token to the end of the list
void add_token(TokenList* list, struct Token token) {
    TokenNode* new_node = (TokenNode*)malloc(sizeof(TokenNode));
    new_node->token = token;
    new_node->next = NULL;

    if (list->tail != NULL) {
        list->tail->next = new_node;
    } else {
        list->head = new_node;
    }

    list->tail = new_node;
}

// Free all memory used by the list
void free_token_list(TokenList* list) {
    TokenNode* current = list->head;
    while (current != NULL) {
        TokenNode* next = current->next;
        free(current->token.token_literal);
        free(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

// Debug: Print your list of tokens
void print_token_list(const TokenList* list) {
    TokenNode* current = list->head;
    while (current != NULL) {
        printf("Token: %-12s  Literal: %s\n",
               (const char*[]){"LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACK", "RIGHT_BRACK", "SEMI", "IDEN", "ASIGN", "RET",
                               "INT"}[current->token.type],
               current->token.token_literal);
        current = current->next;
    }
}
