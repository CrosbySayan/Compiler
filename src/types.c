#include "types.h"

#include <stdio.h>

Token create_token(TokenType type, const char *literal) {
    struct Token t;
    t.type = type;
    t.token_literal = strdup(literal);
    return t;
}

void init_token_list(TokenList *list) {
    list->head = NULL;
    list->tail = NULL;
}

void add_token(TokenList *list, struct Token token) {
    TokenNode *new_node = (TokenNode *)malloc(sizeof(TokenNode));
    new_node->token = token;
    new_node->next = NULL;

    if (list->tail != NULL) {
        list->tail->next = new_node;
    } else {
        list->head = new_node;
    }

    list->tail = new_node;
}

TokenNode *pop_token(TokenList *list) {
    if (list->head == NULL) {
        fprintf(stderr, "Token List is empty returning null");
        return NULL;
    }
    TokenNode *old_head = list->head;

    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = list->head->next;
    }
    return old_head;
}

void free_token(TokenNode *tok) {
    if (tok != NULL) {
        free(tok->token.token_literal);
        free(tok);
    }
}

void free_token_list(TokenList *list) {
    TokenNode *current = list->head;
    while (current != NULL) {
        TokenNode *next = current->next;
        free_token(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

void print_token_list(const TokenList *list) {
    TokenNode *current = list->head;
    while (current != NULL) {
        const char *type_names[] = {"LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACK", "RIGHT_BRACK", "SEMI", "NEG", "BIT_COM",
                                    "LOG_NEG",    "IDEN",        "ASIGN",      "LITERAL",     "RET",  "INT", "ILLEGAL"};
        printf("\033[1;32mToken:\033[0m %-12s  \033[1;32mLiteral:\033[0m %s\n", type_names[current->token.type],
               current->token.token_literal);
        current = current->next;
    }
}
