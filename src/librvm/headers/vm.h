//
// Created by hrs on 27/01/24.
//

#ifndef VM_H
#define VM_H

#include <stddef.h>
#include <stdint.h>

#include "instruction.h"
#include "instruction_buffer.h"

#define NUM_GP_REGS 12

typedef union {
    int32_t  i32;
    uint32_t u32;
    int64_t  i64;
    uint64_t u64;
    float    f32;
    double   f64;
} Register;

typedef struct {
    Register reg[NUM_GP_REGS];
    uint8_t *pc;
    uint8_t *sp;

    uint8_t *memory;
    uint8_t *stack_base;
    uint8_t *heap_base;

    size_t memory_size;
    size_t stack_size;
    size_t heap_size;
} VM;

VM *init_vm(size_t memory_size, size_t stack_size, size_t heap_size);
void free_vm(VM *vm);
void load_program(VM *vm, uint8_t *program, size_t size);
void load_program_from_buffer(VM *vm, InstructionBuffer buffer);
void run(VM *vm);

#endif //VM_H
