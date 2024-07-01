//
// Created by hrs on 27/06/24.
//

#include "parse.h"
#include <stdio.h>
#include <string.h>

InstructionArgumentValue parse_arg(Parser* p, InstructionType type);

Parser* create_parser(unsigned char* buffer, int buffer_size) {
    Parser* p = malloc(sizeof(Parser));
    p->index = 0;
    p->buffer = buffer;
    p->buffer_size = buffer_size;
    p->instructions = CreateBuffer(20);
    p->directives = create_directive_buffer(10);
    p->error = 0;
    return p;
}

void destroy_parser(Parser* p) {
    free(p);
}

void parse(Parser* p) {
    while (p->index < p->buffer_size) {
        Instruction instr;

        if (HALT <= p->buffer[p->index] && p->buffer[p->index] < NUMBER_OF_OPCODE) {
            // Handle instruction
            instr.instruction = (Opcode) p->buffer[p->index];
            p->index++;
            if(p->index >= p->buffer_size) {
                instr.type = IT_void;
                AddBufferData(p->instructions, instr);
                continue;
            }
            instr.type = p->buffer[p->index] % NUMBER_OF_INSTRUCTION_TYPES;
            p->index++;
            if(p->index >= p->buffer_size || p->buffer[p->index] == '\n') {
                AddBufferData(p->instructions, instr);
                continue;
            }
            instr.arg = parse_arg(p, instr.type);
            AddBufferData(p->instructions, instr);
        } else if (p->buffer[p->index] == 255) {
            p->index++;
            if(p->index >= p->buffer_size) {
                printf("Empty directive found during parsing! Terminating.");
                p->error = 1;
                return;
            }
            /*switch (p->buffer[p->index]) { // TODO support parsing strings and identifiers
                case META:
                case DATA:
                case PROGRAM: {
                    instr.instruction = 255;
                    instr.type = p->buffer[p->index];
                    AddBufferData(p->instructions, instr);
                }
                case CONST:
                case NAME:
                case VERSION: {
                    instr.instruction = 255;
                    instr.type = p->buffer[p->index];
                    instr.arg = parse_arg(p, );
                }
            }*/

        } else {
            printf("Unknown byte found during parsing! Terminating.");
            p->error = 1;
            return;
        }
    }
}

// TODO support variable arguments (load x, store x)... Perhaps check if the instruction requires a variable and use a different parse_id function.
InstructionArgumentValue parse_arg(Parser* p, InstructionType type) {
    InstructionArgumentValue arg;
    memset(&arg, 0, sizeof(InstructionArgumentValue));

    // Ensure there are enough bytes in the buffer for each type
    int remaining_bytes = p->buffer_size - p->index;
    switch (type) {
        case IT_i8:
            if (remaining_bytes >= sizeof(int8_t)) {
                arg.i8 = (int8_t)p->buffer[p->index];
                p->index += sizeof(int8_t);
            }
            break;
        case IT_i16:
            if (remaining_bytes >= sizeof(int16_t)) {
                arg.i16 = (int16_t)(p->buffer[p->index] | (p->buffer[p->index + 1] << 8));
                p->index += sizeof(int16_t);
            }
            break;
        case IT_i32:
            if (remaining_bytes >= sizeof(int32_t)) {
                arg.i32 = (int32_t)(
                        p->buffer[p->index] |
                        (p->buffer[p->index + 1] << 8) |
                        (p->buffer[p->index + 2] << 16) |
                        (p->buffer[p->index + 3] << 24));
                p->index += sizeof(int32_t);
            }
            break;
        case IT_i64:
            if (remaining_bytes >= sizeof(int64_t)) {
                arg.i64 = (int64_t)(
                        (uint64_t)p->buffer[p->index] |
                        ((uint64_t)p->buffer[p->index + 1] << 8) |
                        ((uint64_t)p->buffer[p->index + 2] << 16) |
                        ((uint64_t)p->buffer[p->index + 3] << 24) |
                        ((uint64_t)p->buffer[p->index + 4] << 32) |
                        ((uint64_t)p->buffer[p->index + 5] << 40) |
                        ((uint64_t)p->buffer[p->index + 6] << 48) |
                        ((uint64_t)p->buffer[p->index + 7] << 56));
                p->index += sizeof(int64_t);
            }
            break;
        case IT_u8:
            if (remaining_bytes >= sizeof(uint8_t)) {
                arg.u8 = (uint8_t)p->buffer[p->index];
                p->index += sizeof(uint8_t);
            }
            break;
        case IT_u16:
            if (remaining_bytes >= sizeof(uint16_t)) {
                arg.u16 = (uint16_t)(p->buffer[p->index] | (p->buffer[p->index + 1] << 8));
                p->index += sizeof(uint16_t);
            }
            break;
        case IT_u32:
            if (remaining_bytes >= sizeof(uint32_t)) {
                arg.u32 = (uint32_t)(
                        p->buffer[p->index] |
                        (p->buffer[p->index + 1] << 8) |
                        (p->buffer[p->index + 2] << 16) |
                        (p->buffer[p->index + 3] << 24));
                p->index += sizeof(uint32_t);
            }
            break;
        case IT_u64:
            if (remaining_bytes >= sizeof(uint64_t)) {
                arg.u64 = (uint64_t)(
                        (uint64_t)p->buffer[p->index] |
                        ((uint64_t)p->buffer[p->index + 1] << 8) |
                        ((uint64_t)p->buffer[p->index + 2] << 16) |
                        ((uint64_t)p->buffer[p->index + 3] << 24) |
                        ((uint64_t)p->buffer[p->index + 4] << 32) |
                        ((uint64_t)p->buffer[p->index + 5] << 40) |
                        ((uint64_t)p->buffer[p->index + 6] << 48) |
                        ((uint64_t)p->buffer[p->index + 7] << 56));
                p->index += sizeof(uint64_t);
            }
            break;
        case IT_f32:
            if (remaining_bytes >= sizeof(float)) {
                uint32_t temp;
                memcpy(&temp, &p->buffer[p->index], sizeof(float));
                arg.f32 = *(float*)&temp;
                p->index += sizeof(float);
            }
            break;
        case IT_f64:
            if (remaining_bytes >= sizeof(double)) {
                uint64_t temp;
                memcpy(&temp, &p->buffer[p->index], sizeof(double));
                arg.f64 = *(double*)&temp;
                p->index += sizeof(double);
            }
            break;
        default:
            // Handle unsupported type case if needed
            break;
    }

    return arg;
}