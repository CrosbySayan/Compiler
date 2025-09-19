// Simple main file for testing function calls
#include "parser.h"
#include "tokenizer.h"
#include "types.h"
int main() {
    char *input = "int output() {\n return 3;\n }";

    TokenList list;
    init_token_list(&list);

    tokenize(input, &list);
    print_token_list(&list);
    ASTNode *ast = parse(&list);
    pretty_print(ast);
    generate("test_output", ast);
    free_ast(ast);
    return 0;
}
