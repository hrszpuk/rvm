//
// Created by hrs on 27/01/24.
//

#include "headers/vm.h"

#include <stdio.h>
#include <stdlib.h>

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

// NOTE(hrs) instruction buffer is not freed in DestroyVM
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
        Instruction instr = GetBufferData(vm->buffer, vm->ip);
        switch (instr.instruction) {
            case HALT: {
                vm->state = 2;
                break;
            }
            case NOOP: {
                break;
            }
            case PUSH: {
                StackValue value = (StackValue){instr.type, instr.arg};
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
                    fprintf(stderr, "Type mismatch in operation: %d\n", instr.instruction);
                    // Handle error or exit
                    break;
                }

                switch (a.type) {
                    case IT_void:
                        fprintf(stderr, "Invalid operation on void type\n");
                        // Handle error or exit
                        break;
                    case IT_i8:
                        if (instr.instruction == ADD) a.value.i8 += b.value.i8;
                        if (instr.instruction == SUB) a.value.i8 -= b.value.i8;
                        if (instr.instruction == MUL) a.value.i8 *= b.value.i8;
                        if (instr.instruction == DIV) a.value.i8 /= b.value.i8;
                        if (instr.instruction == MOD) a.value.i8 %= b.value.i8;
                        break;
                    case IT_i16:
                        if (instr.instruction == ADD) a.value.i16 += b.value.i16;
                        if (instr.instruction == SUB) a.value.i16 -= b.value.i16;
                        if (instr.instruction == MUL) a.value.i16 *= b.value.i16;
                        if (instr.instruction == DIV) a.value.i16 /= b.value.i16;
                        if (instr.instruction == MOD) a.value.i16 %= b.value.i16;
                        break;
                    case IT_i32:
                        if (instr.instruction == ADD) a.value.i32 += b.value.i32;
                        if (instr.instruction == SUB) a.value.i32 -= b.value.i32;
                        if (instr.instruction == MUL) a.value.i32 *= b.value.i32;
                        if (instr.instruction == DIV) a.value.i32 /= b.value.i32;
                        if (instr.instruction == MOD) a.value.i32 %= b.value.i32;
                        break;
                    case IT_i64:
                        if (instr.instruction == ADD) a.value.i64 += b.value.i64;
                        if (instr.instruction == SUB) a.value.i64 -= b.value.i64;
                        if (instr.instruction == MUL) a.value.i64 *= b.value.i64;
                        if (instr.instruction == DIV) a.value.i64 /= b.value.i64;
                        if (instr.instruction == MOD) a.value.i64 %= b.value.i64;
                        break;
                    case IT_u8:
                        if (instr.instruction == ADD) a.value.u8 += b.value.u8;
                        if (instr.instruction == SUB) a.value.u8 -= b.value.u8;
                        if (instr.instruction == MUL) a.value.u8 *= b.value.u8;
                        if (instr.instruction == DIV) a.value.u8 /= b.value.u8;
                        if (instr.instruction == MOD) a.value.u8 %= b.value.u8;
                        break;
                    case IT_u16:
                        if (instr.instruction == ADD) a.value.u16 += b.value.u16;
                        if (instr.instruction == SUB) a.value.u16 -= b.value.u16;
                        if (instr.instruction == MUL) a.value.u16 *= b.value.u16;
                        if (instr.instruction == DIV) a.value.u16 /= b.value.u16;
                        if (instr.instruction == MOD) a.value.u16 %= b.value.u16;
                        break;
                    case IT_u32:
                        if (instr.instruction == ADD) a.value.u32 += b.value.u32;
                        if (instr.instruction == SUB) a.value.u32 -= b.value.u32;
                        if (instr.instruction == MUL) a.value.u32 *= b.value.u32;
                        if (instr.instruction == DIV) a.value.u32 /= b.value.u32;
                        if (instr.instruction == MOD) a.value.u32 %= b.value.u32;
                        break;
                    case IT_u64:
                        if (instr.instruction == ADD) a.value.u64 += b.value.u64;
                        if (instr.instruction == SUB) a.value.u64 -= b.value.u64;
                        if (instr.instruction == MUL) a.value.u64 *= b.value.u64;
                        if (instr.instruction == DIV) a.value.u64 /= b.value.u64;
                        if (instr.instruction == MOD) a.value.u64 %= b.value.u64;
                        break;
                    case IT_f32:
                        if (instr.instruction == ADD) a.value.f32 += b.value.f32;
                        if (instr.instruction == SUB) a.value.f32 -= b.value.f32;
                        if (instr.instruction == MUL) a.value.f32 *= b.value.f32;
                        if (instr.instruction == DIV) a.value.f32 /= b.value.f32;
                        // MOD is not typically valid for floats
                        if (instr.instruction == MOD) {
                            fprintf(stderr, "Modulo operation not valid on floats\n");
                            // Handle error or exit
                        }
                        break;
                    case IT_f64:
                        if (instr.instruction == ADD) a.value.f64 += b.value.f64;
                        if (instr.instruction == SUB) a.value.f64 -= b.value.f64;
                        if (instr.instruction == MUL) a.value.f64 *= b.value.f64;
                        if (instr.instruction == DIV) a.value.f64 /= b.value.f64;
                        // MOD is not typically valid for floats
                        if (instr.instruction == MOD) {
                            fprintf(stderr, "Modulo operation not valid on floats\n");
                            // Handle error or exit
                        }
                        break;
                }

                PushStack(vm->stack, a);
                break;
            }
            default: {
                printf("Unknown instruction! %d\n", instr.instruction);
                break;
            }
            case LOAD: // TODO
                break;
            case STORE:
                break;
            case BR: {
                vm->ip = instr.arg.i32;
                break;
            }
            case BRF: {
                StackValue a = PopStack(vm->stack);
                if (a.value.i32 == 0) {
                    vm->ip = instr.arg.i32;
                }
                break;
            }
            case BRT: {
                StackValue a = PopStack(vm->stack);
                if (a.value.i32 != 0) {
                    vm->ip = instr.arg.i32;
                }
                break;
            }
            case BEQ:
                break;
            case BGE:
                break;
            case BLE:
                break;
            case BLT:
            case BNE: {
                StackValue b = PopStack(vm->stack);
                StackValue a = PopStack(vm->stack);

                bool condition = false;
                #define BRANCH_COMPARE(op) \
                switch (a.type) { \
                    case IT_i8:   condition = (a.value.i8 op b.value.i8); break; \
                    case IT_i16:  condition = (a.value.i16 op b.value.i16); break; \
                    case IT_i32:  condition = (a.value.i32 op b.value.i32); break; \
                    case IT_i64:  condition = (a.value.i64 op b.value.i64); break; \
                    case IT_u8:   condition = (a.value.u8 op b.value.u8); break; \
                    case IT_u16:  condition = (a.value.u16 op b.value.u16); break; \
                    case IT_u32:  condition = (a.value.u32 op b.value.u32); break; \
                    case IT_u64:  condition = (a.value.u64 op b.value.u64); break; \
                    case IT_f32:  condition = (a.value.f32 op b.value.f32); break; \
                    case IT_f64:  condition = (a.value.f64 op b.value.f64); break; \
                    default:      fprintf(stderr, "Unsupported type in branching operation\n"); break; \
                }

                switch (instr.instruction) {
                    case BEQ: BRANCH_COMPARE(==); break;
                    case BGE: BRANCH_COMPARE(>=); break;
                    case BLE: BRANCH_COMPARE(<=); break;
                    case BLT: BRANCH_COMPARE(<); break;
                    case BNE: BRANCH_COMPARE(!=); break;
                }

                if (condition) {
                    vm->ip = instr.arg.i32;
                }
                break;
            }

            case AND:
            case OR:
            case XOR:
            case SHL:
            case SHR: {
                StackValue b = PopStack(vm->stack);
                StackValue a = PopStack(vm->stack);
                StackValue result = {IT_i32, {.i32 = 0}};  // Default result for invalid operations

                if (a.type != b.type) {
                    fprintf(stderr, "Type mismatch in bitwise operation\n");
                    // Handle error or decide on a strategy for type mismatch
                    break;
                }

                #define BITWISE(op) \
                switch (a.type) { \
                    case IT_i8:   result.value.i8  = a.value.i8  op b.value.i8; break; \
                    case IT_i16:  result.value.i16 = a.value.i16 op b.value.i16; break; \
                    case IT_i32:  result.value.i32 = a.value.i32 op b.value.i32; break; \
                    case IT_i64:  result.value.i64 = a.value.i64 op b.value.i64; break; \
                    case IT_u8:   result.value.u8  = a.value.u8  op b.value.u8; break; \
                    case IT_u16:  result.value.u16 = a.value.u16 op b.value.u16; break; \
                    case IT_u32:  result.value.u32 = a.value.u32 op b.value.u32; break; \
                    case IT_u64:  result.value.u64 = a.value.u64 op b.value.u64; break; \
                    default:      fprintf(stderr, "Unsupported type in bitwise operation\n"); break; \
                }

                switch (instr.instruction) {
                    case AND: BITWISE(&); break;
                    case OR:  BITWISE(|); break;
                    case XOR: BITWISE(^); break;
                    case SHL: BITWISE(<<); break;
                    case SHR: BITWISE(>>); break;
                }

                PushStack(vm->stack, result);
                break;
            }
            case NOT: {
                StackValue a = PopStack(vm->stack);
                StackValue result = {IT_i32, {.i32 = 0}};  // Default result for invalid operations

                switch (a.type) {
                    case IT_i8:   result.value.i8  = ~a.value.i8; break;
                    case IT_i16:  result.value.i16 = ~a.value.i16; break;
                    case IT_i32:  result.value.i32 = ~a.value.i32; break;
                    case IT_i64:  result.value.i64 = ~a.value.i64; break;
                    case IT_u8:   result.value.u8  = ~a.value.u8; break;
                    case IT_u16:  result.value.u16 = ~a.value.u16; break;
                    case IT_u32:  result.value.u32 = ~a.value.u32; break;
                    case IT_u64:  result.value.u64 = ~a.value.u64; break;
                    default:      fprintf(stderr, "Unsupported type in NOT operation\n"); break;
                }

                PushStack(vm->stack, result);
                break;
            }

            case LAND:
            case LOR: {
                StackValue b = PopStack(vm->stack);
                StackValue a = PopStack(vm->stack);
                StackValue result = {IT_i32, {.i32 = 0}};  // Default to false (0)

                if (a.type != b.type) {
                    fprintf(stderr, "Type mismatch in logical operation\n");
                    // Handle error or decide on a strategy for type mismatch
                    break;
                }

                #define LOGICAL(op) \
                switch (a.type) { \
                    case IT_i8:   result.value.i32 = (a.value.i8  op b.value.i8); break; \
                    case IT_i16:  result.value.i32 = (a.value.i16 op b.value.i16); break; \
                    case IT_i32:  result.value.i32 = (a.value.i32 op b.value.i32); break; \
                    case IT_i64:  result.value.i32 = (a.value.i64 op b.value.i64); break; \
                    case IT_u8:   result.value.i32 = (a.value.u8  op b.value.u8); break; \
                    case IT_u16:  result.value.i32 = (a.value.u16 op b.value.u16); break; \
                    case IT_u32:  result.value.i32 = (a.value.u32 op b.value.u32); break; \
                    case IT_u64:  result.value.i32 = (a.value.u64 op b.value.u64); break; \
                    default:      fprintf(stderr, "Unsupported type in logical operation\n"); break; \
                }

                switch (instr.instruction) {
                    case LAND: LOGICAL(&&); break;
                    case LOR:  LOGICAL(||); break;
                }

                PushStack(vm->stack, result);
                break;
            }
            case NEG: {
                StackValue a = PopStack(vm->stack);
                StackValue result = {IT_i32, {.i32 = 0}};  // Default to false (0)

                switch (a.type) {
                    case IT_i8:   result.value.i32 = !a.value.i8; break;
                    case IT_i16:  result.value.i32 = !a.value.i16; break;
                    case IT_i32:  result.value.i32 = !a.value.i32; break;
                    case IT_i64:  result.value.i32 = !a.value.i64; break;
                    case IT_u8:   result.value.i32 = !a.value.u8; break;
                    case IT_u16:  result.value.i32 = !a.value.u16; break;
                    case IT_u32:  result.value.i32 = !a.value.u32; break;
                    case IT_u64:  result.value.i32 = !a.value.u64; break;
                    case IT_f32:  result.value.i32 = !a.value.f32; break;
                    case IT_f64:  result.value.i32 = !a.value.f64; break;
                    default:      fprintf(stderr, "Unsupported type in logical NOT operation\n"); break;
                }

                PushStack(vm->stack, result);
                break;
            }
            case CONV: {
                StackValue a = PopStack(vm->stack);
                StackValue result;
                result.type = instr.type;  // The target type is specified in the instruction

                // Perform conversion based on the target type
                switch (result.type) {
                    case IT_i8:
                        result.value.i8 = (int8_t)a.value.i32;
                        break;
                    case IT_i16:
                        result.value.i16 = (int16_t)a.value.i32;
                        break;
                    case IT_i32:
                        result.value.i32 = (int32_t)a.value.i32;
                        break;
                    case IT_i64:
                        result.value.i64 = (int64_t)a.value.i32;
                        break;
                    case IT_u8:
                        result.value.u8 = (uint8_t)a.value.i32;
                        break;
                    case IT_u16:
                        result.value.u16 = (uint16_t)a.value.i32;
                        break;
                    case IT_u32:
                        result.value.u32 = (uint32_t)a.value.i32;
                        break;
                    case IT_u64:
                        result.value.u64 = (uint64_t)a.value.i32;
                        break;
                    case IT_f32:
                        result.value.f32 = (float)a.value.i32;
                        break;
                    case IT_f64:
                        result.value.f64 = (double)a.value.i32;
                        break;
                    default:
                        fprintf(stderr, "Unsupported conversion type\n");
                        // Handle error
                        break;
                }

                PushStack(vm->stack, result);
                break;
            }
            case EQ:
            case GE:
            case GT:
            case LE:
            case LT:
            case NE: {
                StackValue b = PopStack(vm->stack);
                StackValue a = PopStack(vm->stack);
                StackValue result = {IT_i32, {.i32 = 0}};  // Default to false (0)

                if (a.type != b.type) {
                    fprintf(stderr, "Type mismatch in comparison operation\n");
                    // Handle error or decide on a strategy for type mismatch
                    break;
                }

                #define COMPARE(op) \
                switch (a.type) { \
                    case IT_i8:   result.value.i32 = (a.value.i8 op b.value.i8); break; \
                    case IT_i16:  result.value.i32 = (a.value.i16 op b.value.i16); break; \
                    case IT_i32:  result.value.i32 = (a.value.i32 op b.value.i32); break; \
                    case IT_i64:  result.value.i32 = (a.value.i64 op b.value.i64); break; \
                    case IT_u8:   result.value.i32 = (a.value.u8 op b.value.u8); break; \
                    case IT_u16:  result.value.i32 = (a.value.u16 op b.value.u16); break; \
                    case IT_u32:  result.value.i32 = (a.value.u32 op b.value.u32); break; \
                    case IT_u64:  result.value.i32 = (a.value.u64 op b.value.u64); break; \
                    case IT_f32:  result.value.i32 = (a.value.f32 op b.value.f32); break; \
                    case IT_f64:  result.value.i32 = (a.value.f64 op b.value.f64); break; \
                    default:      fprintf(stderr, "Unsupported type in comparison operation\n"); break; \
                }

                switch (instr.instruction) {
                    case EQ:  COMPARE(==); break;
                    case GE:  COMPARE(>=); break;
                    case GT:  COMPARE(>); break;
                    case LE:  COMPARE(<=); break;
                    case LT:  COMPARE(<); break;
                    case NE:  COMPARE(!=); break;
                }

                PushStack(vm->stack, result);
                break;
            }
        }
        vm->ip++;
    }
}

void StopVM(VM* vm) {
    vm->state = 2;
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

