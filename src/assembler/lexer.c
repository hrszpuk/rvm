//
// Created by hrs on 31/01/24.
//

#include "headers/lexer.h"

#include <stdlib.h>

Lexer* CreateLexer() {
    Lexer* lexer = malloc(sizeof(Lexer));
    lexer->file = NULL;
    lexer->buffer = NULL;
    lexer->path = NULL;
    lexer->tokens = NULL;
    lexer->index = 0;
    lexer->line = 1;
    lexer->column = 1;
    return lexer;
}


Lexer* CreateLexerFromFilename(const char* path) {
    Lexer* lexer = CreateLexer();
    lexer->file = fopen(path, "r");
    lexer->path = path;

    if (lexer->file == NULL) {
        printf("Error: Could not open file '%s'\n", path);
        free(lexer);
        return NULL;
    }

    lexer->buffer = malloc(sizeof(char));
    lexer->buffer[0] = '\0';

    lexer->tokens = malloc(sizeof(Token));
    lexer->tokens[0].type = END_OF_FILE;

    return lexer;
}

// NOTE(hrs): This does not destroy the tokens. It is presumed that the tokens are owned by the parser.
void DestroyLexer(Lexer* lexer) {
    if (lexer->file != NULL) {
        fclose(lexer->file);
    }

    if (lexer->buffer != NULL) {
        free(lexer->buffer);
    }

    free(lexer);
}

