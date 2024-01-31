//
// Created by hrs on 31/01/24.
//

#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "token.h"

typedef struct {
    FILE* file;
    char* buffer;
    char* path;
    Token* tokens;
    int index;
    int line;
    int column;
} Lexer;

Lexer* CreateLexer();
Lexer* CreateLexerFromFilename(const char* path);
void DestroyLexer(Lexer* lexer);
void DumpLexer(Lexer* lexer);
void Lex(Lexer* lexer);


#endif //LEXER_H
