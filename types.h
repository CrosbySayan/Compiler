typedef enum {
    // Defines the type of token
} TokenType;

struct Token {
    TokenType type;       // Type of token
    char* token_literal;  // The literal character in the token
};
