#include "parser.h"
#include "stdlib.h"
#include "stdio.h"

ASTNode *parse(TokenList *token_list) {
    TokenNode *curr = token_list->head;

    // build AST for program
    ASTNode *program_node = (ASTNode *)malloc(sizeof(ASTNode));
    program_node->type = PROG_NODE;
    program_node->next = NULL;

    curr = curr->next;
    if (curr->token.type != IDEN) {
        // throw error
        exit(1);
    }

    // build AST for function
    ASTNode *function_node = (ASTNode *)malloc(sizeof(ASTNode));
    function_node->type = FUNC_NODE;
    function_node->next = NULL;
    function_node->data.ident = curr->token.token_literal;

    // link child
    program_node->child = function_node;

    curr = curr->next;
    if (curr->token.type != RET) {
        // throw error
        exit(1);
    }

    // build AST for return
    ASTNode *return_node = (ASTNode *)malloc(sizeof(ASTNode));
    return_node->type = RET_NODE;
    return_node->next = NULL;

    // link child
    function_node->child = return_node;

    curr = curr->next;
    if (curr->token.type != INT) {
        // throw error
        exit(1);
    }

    // build AST for int
    ASTNode *int_node = (ASTNode *)malloc(sizeof(ASTNode));
    int_node->type = INT_NODE;
    int_node->next = NULL;
    int_node->data.value = atoi(curr->token.token_literal);

    // link child
    return_node->child = int_node;

    curr = curr->next;
    if (curr->token.type != SEMI) {
        // throw error
        exit(1);
    }
    return program_node;
}

void free_ast(ASTNode *root) {
    if (root == NULL) {
        return;
    }

    // recursively free ASTNodes
    free_ast(root->child);
    free_ast(root->next);

    free(root);
}

void generate(ASTNode *root) {
    FILE *fptr;
    fptr = fopen("return_2.s", "w");
    fprintf(fptr, "");
    fclose(fptr);
}
