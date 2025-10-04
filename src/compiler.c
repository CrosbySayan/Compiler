#include <libgen.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include "parser.h"
#include "tokenizer.h"
#include "types.h"

///@brief Takes in an assembly file and turns it into an executable
///@param asm_filename Name of the Assembly file
///@param output_filename Name of executable
/// NOTE: gcc command is not thread safe, may want to look at new options if we want to compile a bunch files
/// concurrently
int invoke_gcc(const char *asm_filename, const char *output_filename) {
    char command[256];

    // Build GCC command
    snprintf(command, sizeof(command), "gcc -m64 %s -o %s", asm_filename, output_filename);

    int result = system(command);

    if (result == -1) {
        fprintf(stderr, "Failed to execute GCC\n");
        return -1;
    }

    // Check GCC succeeded
    if (WEXITSTATUS(result) != 0) {
        fprintf(stderr, "GCC compilation failed\n");
        return -1;
    }

    return 0;
}

///@brief Gets the filename for a given path and removes the '.' extention so it can be used for the executable name
///@param filepath a c-string that is a path to a given file
///@return a c-string with just the file's name (string must be freed by caller).
char *get_executable_name(char *filepath) {
    // Simply remove the .c extension, keeping the full path
    char *output = strdup(filepath);
    size_t len = strlen(output);

    if (len > 2 && strcmp(output + len - 2, ".c") == 0) {
        output[len - 2] = '\0';  // Remove .c extension
    }

    return output;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Wrong number of arguments: %i, expects 1", argc);
        return 1;
    }

    FILE *filePtr = fopen(argv[1], "r");
    char *filename = get_executable_name(argv[1]);
    if (filePtr == NULL) {
        fprintf(stderr, "Failed to open file at path %s\n", argv[0]);
    }

    TokenList tokenList;
    init_token_list(&tokenList);

    char buffer[256];
    // Read the file of a certain buffer size and then create tokens of it
    while (fgets(buffer, sizeof(buffer), filePtr) != NULL) {
        tokenize(buffer, &tokenList);
    }

    // Debugging Token List print out
    print_token_list(&tokenList);
    // Parse AST nodes from token list
    ASTNode *ast = parse(&tokenList);

    // Debugging AST print
    pretty_print(ast);

    // Generate Assembly
    char asm_filename[256];
    snprintf(asm_filename, sizeof(asm_filename), "%s.s", filename);
    generate(asm_filename, ast);
    // Turn Assembly -> an executable
    invoke_gcc(asm_filename, filename);

    // Cleanup
    free_ast(ast);
    fclose(filePtr);
    free(filename);
    return 0;
}
