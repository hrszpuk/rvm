//
// Created by hrs on 24/01/24.
//

#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#define OPCODE_ERROR OPCODE_ENUM_LENGTH

typedef enum {
    HALT,
    PUSH,
    ADD,
    OPCODE_ENUM_LENGTH  // This isn't a value opcode instruction.
} Opcode;

// TODO this should be a hashmap/dictionary
static const char* OpcodeStringMap[OPCODE_ENUM_LENGTH] = {
    [HALT] = "halt",
    [PUSH] = "push",
    [ADD] = "add",
};

typedef struct {
    Opcode code;
    int argument_count;
} Instruction;

Opcode BytecodeToOpcode(const char*);

#endif //INSTRUCTION_H
