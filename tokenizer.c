#include <stdio.h>

#include "types.h"
// Read file
// Returns a linked list of all the tokens in the file
void tokenizeFile() {
    FILE* fd = fopen("./token-test.c", "r");
    // After opening the file read the char by char with a buffer
    char ch;

    char buffer[1024];
    char last_char = buffer[0];
    while ((ch = fgetc(fd)) != EOF) {
        // Single Char check/space or newline check
        // if pass check the buffer before is a valid keyword
        // else add the char to buffer
    }
}

int main() { return 0; }
