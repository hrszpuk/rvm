//
// Created by hrs on 24/01/24.
//

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

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
    InstructionCode code;
    int argument_count;
} Instruction;

InstructionCode* BytecodeToOpcode(char*);
char* OpcodeToBytecode(InstructionCode);



#endif //INSTRUCTION_H
