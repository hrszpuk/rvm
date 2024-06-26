//
// Created by hrs on 26/06/24.
//

#ifndef RVM_SYMBOL_TABLE_H
#define RVM_SYMBOL_TABLE_H

typedef enum {
    INT
} SymbolType;

typedef struct {
    char *name;
    void* value;
    SymbolType type;
    int scope;
} Symbol;

typedef struct {
    Symbol* symbols;
    int symbol_count;
} SymbolTable;

#endif //RVM_SYMBOL_TABLE_H
