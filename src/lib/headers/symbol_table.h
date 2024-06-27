//
// Created by hrs on 26/06/24.
//

#ifndef RVM_SYMBOL_TABLE_H
#define RVM_SYMBOL_TABLE_H

#include <stdint.h>

typedef enum {
    ST_i8, ST_i16, ST_i32, ST_i64,
    ST_u8, ST_u16, ST_u32, ST_u64,
    ST_f32, ST_f64
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
