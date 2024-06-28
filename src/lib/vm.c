//
// Created by hrs on 27/01/24.
//

#include "headers/vm.h"

#include <stdio.h>
#include <stdlib.h>

#include "../assembler/headers/translator.h"

// NOTE(hrs): default buffer is NULL and must be set before running the VM. (Temporary, see LoadBytecode).
VM* CreateVM(const int stackCapacity) {
    VM* vm = malloc(sizeof(VM));
    vm->stack = CreateStack(stackCapacity);
    vm->buffer = NULL;
    vm->ip = 0;
    vm->state = 0;
    vm->debug = 0;
    return vm;
}

// NOTE(hrs): bytecode buffer must contain TranslationResult data
void LoadBytecode(VM* vm, InstructionBuffer* bytecode) {
    vm->buffer = bytecode;
}

// NOTE(hrs) instruction buffer is not free'd in DestroyVM
void DestroyVM(VM* vm) {
    FreeStack(vm->stack);
    free(vm);
}

void RunVM(VM* vm) {
    vm->state = 0;

    while (vm->state == 0) {
        if (vm->ip >= vm->buffer->count) {
            StopVM(vm);
            return;
        }

        // Fetch instruction, apply it, and increment instruction pointer.
        Instruction wordbyte = GetBufferData(vm->buffer, vm->ip);
        switch (wordbyte.instruction) {
            case HALT: {
                vm->state = 2;
                break;
            }
            case NOOP: {
                break;
            }
            case PUSH: {
                StackValue value = (StackValue){wordbyte.type, wordbyte.arg};
                PushStack(vm->stack, value);
                break;
            }
            case POP: {
                PopStack(vm->stack);
                break;
            }
            case DUP: {
                PushStack(vm->stack, TopStack(vm->stack));
                break;
            }
            case SWAP: {
                StackValue a = PopStack(vm->stack);
                StackValue b = PopStack(vm->stack);
                PushStack(vm->stack, b);
                PushStack(vm->stack, a);
                break;
            }
            case ADD:
            case SUB:
            case MUL:
            case DIV:
            case MOD: {
                StackValue b = PopStack(vm->stack);
                StackValue a = PopStack(vm->stack);

                if (a.type != b.type) {
                    fprintf(stderr, "Type mismatch in operation: %d\n", wordbyte.instruction);
                    // Handle error or exit
                    break;
                }

                switch (a.type) {
                    case IT_void:
                        fprintf(stderr, "Invalid operation on void type\n");
                        // Handle error or exit
                        break;
                    case IT_i8:
                        if (wordbyte.instruction == ADD) a.value.i8 += b.value.i8;
                        if (wordbyte.instruction == SUB) a.value.i8 -= b.value.i8;
                        if (wordbyte.instruction == MUL) a.value.i8 *= b.value.i8;
                        if (wordbyte.instruction == DIV) a.value.i8 /= b.value.i8;
                        if (wordbyte.instruction == MOD) a.value.i8 %= b.value.i8;
                        break;
                    case IT_i16:
                        if (wordbyte.instruction == ADD) a.value.i16 += b.value.i16;
                        if (wordbyte.instruction == SUB) a.value.i16 -= b.value.i16;
                        if (wordbyte.instruction == MUL) a.value.i16 *= b.value.i16;
                        if (wordbyte.instruction == DIV) a.value.i16 /= b.value.i16;
                        if (wordbyte.instruction == MOD) a.value.i16 %= b.value.i16;
                        break;
                    case IT_i32:
                        if (wordbyte.instruction == ADD) a.value.i32 += b.value.i32;
                        if (wordbyte.instruction == SUB) a.value.i32 -= b.value.i32;
                        if (wordbyte.instruction == MUL) a.value.i32 *= b.value.i32;
                        if (wordbyte.instruction == DIV) a.value.i32 /= b.value.i32;
                        if (wordbyte.instruction == MOD) a.value.i32 %= b.value.i32;
                        break;
                    case IT_i64:
                        if (wordbyte.instruction == ADD) a.value.i64 += b.value.i64;
                        if (wordbyte.instruction == SUB) a.value.i64 -= b.value.i64;
                        if (wordbyte.instruction == MUL) a.value.i64 *= b.value.i64;
                        if (wordbyte.instruction == DIV) a.value.i64 /= b.value.i64;
                        if (wordbyte.instruction == MOD) a.value.i64 %= b.value.i64;
                        break;
                    case IT_u8:
                        if (wordbyte.instruction == ADD) a.value.u8 += b.value.u8;
                        if (wordbyte.instruction == SUB) a.value.u8 -= b.value.u8;
                        if (wordbyte.instruction == MUL) a.value.u8 *= b.value.u8;
                        if (wordbyte.instruction == DIV) a.value.u8 /= b.value.u8;
                        if (wordbyte.instruction == MOD) a.value.u8 %= b.value.u8;
                        break;
                    case IT_u16:
                        if (wordbyte.instruction == ADD) a.value.u16 += b.value.u16;
                        if (wordbyte.instruction == SUB) a.value.u16 -= b.value.u16;
                        if (wordbyte.instruction == MUL) a.value.u16 *= b.value.u16;
                        if (wordbyte.instruction == DIV) a.value.u16 /= b.value.u16;
                        if (wordbyte.instruction == MOD) a.value.u16 %= b.value.u16;
                        break;
                    case IT_u32:
                        if (wordbyte.instruction == ADD) a.value.u32 += b.value.u32;
                        if (wordbyte.instruction == SUB) a.value.u32 -= b.value.u32;
                        if (wordbyte.instruction == MUL) a.value.u32 *= b.value.u32;
                        if (wordbyte.instruction == DIV) a.value.u32 /= b.value.u32;
                        if (wordbyte.instruction == MOD) a.value.u32 %= b.value.u32;
                        break;
                    case IT_u64:
                        if (wordbyte.instruction == ADD) a.value.u64 += b.value.u64;
                        if (wordbyte.instruction == SUB) a.value.u64 -= b.value.u64;
                        if (wordbyte.instruction == MUL) a.value.u64 *= b.value.u64;
                        if (wordbyte.instruction == DIV) a.value.u64 /= b.value.u64;
                        if (wordbyte.instruction == MOD) a.value.u64 %= b.value.u64;
                        break;
                    case IT_f32:
                        if (wordbyte.instruction == ADD) a.value.f32 += b.value.f32;
                        if (wordbyte.instruction == SUB) a.value.f32 -= b.value.f32;
                        if (wordbyte.instruction == MUL) a.value.f32 *= b.value.f32;
                        if (wordbyte.instruction == DIV) a.value.f32 /= b.value.f32;
                        // MOD is not typically valid for floats
                        if (wordbyte.instruction == MOD) {
                            fprintf(stderr, "Modulo operation not valid on floats\n");
                            // Handle error or exit
                        }
                        break;
                    case IT_f64:
                        if (wordbyte.instruction == ADD) a.value.f64 += b.value.f64;
                        if (wordbyte.instruction == SUB) a.value.f64 -= b.value.f64;
                        if (wordbyte.instruction == MUL) a.value.f64 *= b.value.f64;
                        if (wordbyte.instruction == DIV) a.value.f64 /= b.value.f64;
                        // MOD is not typically valid for floats
                        if (wordbyte.instruction == MOD) {
                            fprintf(stderr, "Modulo operation not valid on floats\n");
                            // Handle error or exit
                        }
                        break;
                }

                PushStack(vm->stack, a);
                break;
            }
            default: {
                printf("Unknown instruction! %d\n", wordbyte.instruction);
                break;
            }
        }
        vm->ip++;
    }
}

void StopVM(VM* vm) {
    vm->state = 2;
    ClearBufferData(vm->buffer);
}

void DumpVM(VM* vm) {
    PrintStack(vm->stack);
    printf("InstructionBuffer dump:\n");
    for (int i = 0; i < vm->ip; i++) {
        Instruction j = GetBufferData(vm->buffer, i);
        printf("%d: {%d, %d, %d}\n", i, (int)j.instruction, (int)j.type, (int)j.arg.i32);
    }
    printf("Instruction Pointer: %d\n", vm->ip);
    printf("State: %d\n", vm->state);
    printf("Debug: %d\n", vm->debug);
}

