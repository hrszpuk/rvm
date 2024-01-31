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
