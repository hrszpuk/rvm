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

typedef union {
    int8_t i8;
    int16_t i16;
    int32_t i32;
    int64_t i64;
    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
    float f32;
    double f64;
} SymbolValue;

typedef struct Symbol {
    char* name;
    SymbolValue value;
    SymbolType type;
    struct Symbol *next;
} Symbol;

typedef struct {
    Symbol* symbols;
    int symbol_count;
} SymbolTable;

#endif //RVM_SYMBOL_TABLE_H
