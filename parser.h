#ifndef PARSER_H
#define PARSER_H

#include "types.h"

// Defines the types of ASTNodes available
typedef enum {
    PROG_NODE,
    FUNC_NODE,
    RET_NODE,
    INT_NODE,
} NodeType;

// Declares an ASTNode struct
typedef struct ASTNode {
    NodeType type;
    union {
        int value;          // corresponds to INT_NODE
        char *ident;        // program identifier => PROG_NODE
    } data;                 // a union will store the data for specific types
    struct ASTNode *child;  // e.g. return function
    struct ASTNode *next;   // e.g. next function
} ASTNode;

// Returns the root node of the AST
ASTNode *parse(TokenList *token_list);

void free_ast(ASTNode *root);

void pretty_print(ASTNode *root);

#endif
