#include "parser.h"

#include "stdio.h"
#include "stdlib.h"
#include "types.h"

// helper function for confirming token types
// Checks a given token matches the type we expect if it does iterate to the next token.
// Throws if we get an invalid token
TokenNode *expectWithValue(TokenList *tokens, TokenType type) {
    if (!tokens || !tokens->head) {
        fprintf(stderr, "ERROR: Unexpected end of tokens.\n");
        exit(1);
    }

    if (tokens->head->token.type != type) {
        fprintf(stderr, "ERROR: token %s does not match expected type.\n", tokens->head->token.token_literal);
        exit(1);
    }

    return pop_token(tokens);
}

void expect(TokenList *tokens, TokenType type) { free_token(expectWithValue(tokens, type)); }

ASTNode *createASTNode(NodeType type) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = type;
    node->child = NULL;
    node->next = NULL;
    return node;
}

//<unary_op> ::= "!" | "~" | "-"
ASTNode *parse_unaryOp(TokenList *tokens) {
    ASTNode *unaryOp_node = createASTNode(UNARYOP_NODE);

    TokenNode *tok = pop_token(tokens);

    if (tok->token.type == BIT_COM || tok->token.type == NEG || tok->token.type == LOG_NEG) {
        // Add it to the node
        unaryOp_node->data.ident = tok->token.token_literal;  // or however you store the operator
    } else {
        fprintf(stderr, "ERROR: token %s does not match expected type.\n", tokens->head->token.token_literal);
        exit(1);
    }
    return unaryOp_node;
}

//<exp> ::= <unary_op> <exp> | <int>
ASTNode *parse_expression(TokenList *tokens) {
    if (tokens->head->token.type == LITERAL) {
        ASTNode *expression_node = createASTNode(INT_NODE);
        TokenNode *exp = expectWithValue(tokens, LITERAL);
        expression_node->data.value = atoi(exp->token.token_literal);
        free_token(exp);
        return expression_node;
    } else {
        ASTNode *unary_node = parse_unaryOp(tokens);
        unary_node->child = parse_expression(tokens);
        return unary_node;
    }
}

//<statement> ::= "return" <exp> ";"
ASTNode *parse_statement(TokenList *tokens) {
    ASTNode *statement_node = createASTNode(RET_NODE);
    statement_node->type = RET_NODE;  // Note: should probably change this to the more general statement later

    expect(tokens, RET);
    statement_node->child = parse_expression(tokens);
    expect(tokens, SEMI);

    return statement_node;
}

//<function> ::= "int" <id> "(" ")" "{" <statement> "}"
ASTNode *parse_func(TokenList *tokens) {
    ASTNode *function_node = createASTNode(FUNC_NODE);

    expect(tokens, INT);

    TokenNode *iden = expectWithValue(tokens, IDEN);
    function_node->data.ident = strdup(iden->token.token_literal);
    expect(tokens, LEFT_PAREN);
    expect(tokens, RIGHT_PAREN);
    expect(tokens, LEFT_BRACK);
    // statement
    function_node->child = parse_statement(tokens);
    expect(tokens, RIGHT_BRACK);

    free_token(iden);
    return function_node;
}

ASTNode *parse_prog(TokenList *tokens) {
    ASTNode *program_node = createASTNode(PROG_NODE);
    program_node->child = parse_func(tokens);
    return program_node;
}

ASTNode *parse(TokenList *token_list) { return parse_prog(token_list); }

void free_ast(ASTNode *root) {
    if (root == NULL) {
        return;
    }
    if (root->type == FUNC_NODE && root->data.ident) {
        free(root->data.ident);
    }
    // recursively free ASTNodes
    free_ast(root->child);
    free_ast(root->next);

    free(root);
}

void generate_node(ASTNode *node, FILE *fptr) {
    switch (node->type) {
        case PROG_NODE:
            generate_node(node->child, fptr);
            break;
        case FUNC_NODE:
            fprintf(fptr, ".globl %s\n", node->data.ident);
            fprintf(fptr, "%s:\n", node->data.ident);
            generate_node(node->child, fptr);
            break;
        case RET_NODE:
            generate_node(node->child, fptr);
            fprintf(fptr, "ret\n");
            break;
        case INT_NODE:
            fprintf(fptr, "movl $%d, %%eax\n", node->data.value);
            break;
        case UNARYOP_NODE:
            // Write special things based on chars
            break;
    }
}

void generate(char *filename, ASTNode *root) {
    FILE *fptr = fopen(filename, "w");
    if (fptr == NULL) {
        // throw error
        exit(1);
    }
    generate_node(root, fptr);
    fclose(fptr);
}

void delete_file(char *filename) {
    if (remove(filename) == 0) {
        exit(0);
    } else {
        exit(1);
    }
}

void pretty_print_helper(ASTNode *node, int depth) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < depth; i++) {
        printf(" ");
    }

    switch (node->type) {
        case PROG_NODE:
            // PROGRAM START
            if (node->child) {
                pretty_print_helper(node->child, depth);
            }
            break;

        case FUNC_NODE:
            printf("FUN INT %s:\n", node->data.ident);

            // Print params (empty for now)
            for (int i = 0; i < depth + 1; i++) {
                printf(" ");
            }
            printf("params: ()\n");

            // Print body
            for (int i = 0; i < depth + 1; i++) {
                printf(" ");
            }
            printf("body:\n");
            if (node->child) {
                pretty_print_helper(node->child, depth + 2);
            }
            break;
        case RET_NODE:
            printf("RETURN ");
            if (node->child) {
                pretty_print_helper(node->child, 1);
            } else {
                printf("\n");
            }
            break;
        case INT_NODE:
            printf("Int<%d>\n", node->data.value);
            break;
        case UNARYOP_NODE:
            printf("%s", node->data.ident);
            if (node->child) {
                pretty_print_helper(node->child, 0);
            } else {
                printf("\n");
            }
            break;
        default:
            printf("UNKNOWN NODE\n");
            break;
    }
    if (node->next) {
        pretty_print_helper(node->next, depth);
    }
}

// Debug Pretty Print
void pretty_print(ASTNode *root) { pretty_print_helper(root, 0); }
