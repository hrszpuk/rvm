//
// Created by hrs on 31/01/24.
//

#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    UNKNOWN,
    END_OF_FILE,
    END_OF_LINE,
} TokenType;

TokenType KeywordToTokenType(char* keyword); // Returns IDENTIFIER if the keyword is not recognised.

typedef struct {
    char* value;
    int line;
    int column;
    TokenType type;
} Token;

Token* CreateToken(char* value, const int line, const int column, const TokenType type);
void DestroyToken(Token* token);


#endif //TOKEN_H
