//
// Created by hrs on 26/01/24.
//

#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>

#define NUMBER_OF_OPCODE 37

typedef enum {
    // Misc
    HALT,
    NOOP,

    // Load/Store
    LOAD,
    STORE,

    // Stack Manipulation
    PUSH,
    POP,
    DUP,
    SWAP,

    // Branching
    BR,
    BRF,
    BRT,
    BEQ,
    BGE,
    BGT,
    BLE,
    BLT,
    BNE,

    // Arithmetic
    ADD,
    SUB,
    DIV,
    MUL,
    MOD,

    // Bitwise
    AND,
    OR,
    XOR,
    SHL,
    SHR,
    NOT,

    // Logical
    LAND,
    LOR,
    NEG,

    CONV, // Conversion (convert between types)

    // Comparison
    EQ,
    GE,
    GT,
    LE,
    LT,
    NE,
} Opcode;

typedef enum {
    IT_void,
    IT_i8, IT_i16, IT_i32, IT_i64,
    IT_u8, IT_u16, IT_u32, IT_u64,
    IT_f32, IT_f64
} InstructionType;
#define NUMBER_OF_INSTRUCTION_TYPES 11

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
} InstructionArgumentValue;

typedef struct {
    Opcode instruction;
    InstructionType type;
    InstructionArgumentValue arg;
} Instruction;

typedef struct {
    int count;
    int capacity;
    Instruction* instructions;
} InstructionBuffer;

InstructionBuffer* CreateBuffer(int capacity); // Create a new buffer with the specified capacity.
void DestroyBuffer(InstructionBuffer* buffer); // Destroy the buffer and free all memory associated with it.

Instruction GetBufferData(const InstructionBuffer* buffer, int index); // Get the data at the specified index.
void SetBufferData(const InstructionBuffer* buffer, int index, Instruction element); // Set the data at the specified index.
void AddBufferData(InstructionBuffer* buffer, Instruction element); // Add data to the end of the buffer.
void RemoveBufferData(const InstructionBuffer* buffer, int index); // Remove data from the buffer at the specified index.
void ClearBufferData(InstructionBuffer* buffer); // Clear the buffer and free the memory associated with it's data.

#endif //BUFFER_H
