#include "tokenizer.h"

#include <ctype.h>
#include <stdbool.h>
#include <string.h>

bool is_breakpoint(char point) {
    switch (point) {
        case '(':
        case ')':
        case '{':
        case '}':
        case ';':
        case ' ':
        case '\n':
        case '=':
        case '\t':
        case '\0':
            return true;
        default:
            return false;
    }
}

TokenType fetchCharToken(char tokenChar) {
    if (isdigit(tokenChar)) {
        // number things
        return LITERAL;
    } else if (isalpha(tokenChar) || tokenChar == '_') {
        // letter things
        return IDEN;
    } else {
        return ILLEGAL;
    }
}

void multiToken(char **tokenStart, TokenList *list) {
    char *start = *tokenStart;
    int pointer = 0;
    TokenType tag = ILLEGAL;
    bool flag = false;

    while (start[pointer] != '\0' && !is_breakpoint(start[pointer])) {
        char currentChar = start[pointer];
        if (!flag) {
            // Set TokenType tag
            tag = fetchCharToken(currentChar);
            flag = true;
            pointer++;
        } else {
            // What is this char? does it match the current string of chars' type?
            if (tag == ILLEGAL || fetchCharToken(currentChar) != tag) {
                tag = ILLEGAL;
            }
            pointer++;
        }
    }

    // Now with the full word determine if it is a keyword

    if (pointer > 0) {
        char tokenValue[pointer + 1];
        strncpy(tokenValue, start, pointer);
        tokenValue[pointer] = '\0';

        // Check for keywords
        if (tag == IDEN) {
            if (strcmp(tokenValue, "int") == 0) {
                tag = INT;
            } else if (strcmp(tokenValue, "return") == 0) {
                tag = RET;
            }
        }

        add_token(list, create_token(tag, tokenValue));
    }
    *tokenStart += pointer;
}
//  Returns a linked list of all the tokens in the file
void tokenize(char *buff, TokenList *list) {
    char *currentPoint = buff;

    while (*currentPoint != '\0') {
        // Skip whitespace
        if (*currentPoint == ' ' || *currentPoint == '\n' || *currentPoint == '\t') {
            currentPoint++;
            continue;
        }

        switch (*currentPoint) {
            case '(':
                add_token(list, create_token(LEFT_PAREN, "("));
                currentPoint++;
                break;
            case ')':
                add_token(list, create_token(RIGHT_PAREN, ")"));
                currentPoint++;
                break;
            case '{':
                add_token(list, create_token(LEFT_BRACK, "{"));
                currentPoint++;
                break;
            case '}':
                add_token(list, create_token(RIGHT_BRACK, "}"));
                currentPoint++;
                break;
            case ';':
                add_token(list, create_token(SEMI, ";"));
                currentPoint++;
                break;
            case '=':
                add_token(list, create_token(ASIGN, "="));
                currentPoint++;
                break;
            default:
                // Multi character token - multiToken will advance currentPoint
                multiToken(&currentPoint, list);
                break;
        }
    }
}

// int main() {
//   const char *input = "int main() {\n return 0;\n }";
//
//   printf("Input: \"%s\"\n", input);
//   printf("=====================================\n");
//
//   TokenList list;
//   init_token_list(&list);
//
//   char *buffer = strdup(input);
//   tokenize(buffer, &list);
//   // Print the tokens
//   print_token_list(&list);
//
//   // Cleanup
//   free(buffer);
//   free_token_list(&list);
//
//   return 0;
// }
