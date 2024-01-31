//
// Created by hrs on 31/01/24.
//

#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    // Misc
    UNKNOWN,
    END_OF_FILE,
    END_OF_LINE,

    // Values
    IDENTIFIER,
    NUMBER,
    FLOAT,
    STRING,
    CHAR,

    // Blocks
    DOT_CODE,
    DOT_DATA,
    DOT_META,

    // Types
    KW_i8,
    KW_i16,
    KW_i32,
    KW_i64,
    KW_u8,
    KW_u16,
    KW_u32,
    KW_u64,
    KW_f32,
    KW_f64,

    // Meta instructions
    DOT_EXPORT,
    DOT_IMPORT,

    // Data instructions
    DOT_CONST,
    DOT_VAR,
    DOT_STRUCT,

    // Code instructions (Misc)
    HALT,
    NOOP,

    // Code instructions (Stack)
    LOAD,
    STORE,
    PUSH,
    POP,
    DUP,
    SWAP,

    // Code instructions (Arithmetic)
    ADD,
    SUB,
    DIV,
    MUL,
    MOD,
    INC,
    DEC,

    // Code instructions (Control flow)
    JMP,
    JMPC,

    // Code instructions (Functions)
    CALL,
    RET,
    BEGIN,
    END,

    // Code instructions (Pointers)
    ADDR,
    DEREF,
    TYPEOF,

    // Code instructions (Comparisons)
    EQ,
    NEQ,
    LT,
    GT,
    LTE,
    GTE,

    // Code instructions (Bitwise)
    AND,
    OR,
    XOR,
    NOT,
    SHL,
    SHR,

    // Code instructions (Logic)
    LAND,
    LOR,
    LNOT,

    // DO NOT USE
    TOKEN_ENUM_LENGTH
} TokenType;

TokenType KeywordToTokenType(char* keyword); // Returns IDENTIFIER if the keyword is not recognised.

typedef struct {
    char* value;
    int line;
    int column;
    TokenType type;
} Token;

Token* CreateToken(char* value, const int line, const int column, const TokenType type);
void DestroyToken(Token* token);


#endif //TOKEN_H
