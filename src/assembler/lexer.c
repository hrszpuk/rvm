//
// Created by hrs on 31/01/24.
//

#include "headers/lexer.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

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

void DumpLexer(Lexer* lexer) {
    printf("Lexer:\n");
    printf("  Path: %s\n", lexer->path);
    printf("  Index: %d\n", lexer->index);
    printf("  Line: %d\n", lexer->line);
    printf("  Column: %d\n", lexer->column);
    printf("  Buffer: %s\n", lexer->buffer);
    printf("  Tokens:\n");
    for (int i = 0; lexer->tokens[i].type != END_OF_FILE; i++) {
        printf("    Token %d: %s\n", i, TokenTypeToString[lexer->tokens[i].type]);
    }
}

void consume(Lexer* lexer) {
    lexer->c = fgetc(lexer->file);
    lexer->column++;
    lexer->index++;

    if (lexer->c == '\n') {
        lexer->line++;
        lexer->column = 0;
        consume(lexer);
    }
}

void load(Lexer* lexer) {
    lexer->buffer = realloc(lexer->buffer, sizeof(char) * (strlen(lexer->buffer) + 2));
    lexer->buffer[strlen(lexer->buffer) + 1] = '\0';
    lexer->buffer[strlen(lexer->buffer)] = lexer->c;
}

void Lex(Lexer* lexer) {
    while(true) {
        consume(lexer);
        if (isalpha(lexer->c)) {
            // Get identifier/keyword
            lexIdentifier(lexer);
        } else if (lexer->c == '.') {
            // Get identifier (assume .BLOCK or .COMMAND)
            lexBlockOrCommand(lexer);
        } else if (isdigit(lexer->c)) {
            // Get number
            lexNumber(lexer);
        } else if (lexer->c == '"') {
            // Get string
            lexString(lexer);
        } else if (lexer->c == '\'') {
            // Get character
            lexCharacter(lexer);
        } else if (lexer->c == EOF) {
            // Handle end of file
            lexer->Tokens = realloc(lexer->Tokens, sizeof(Token) * (lexer->tokens_size + 1));
            lexer->Tokens[lexer->tokens_size] = CreateToken(NULL, lexer->line, lexer->column, END_OF_FILE);
            lexer->tokens_size++;
            break;
        } else {
            // Handle unknown (give to parser anyway)
            lexUnknown(lexer);
        }
    }
}

