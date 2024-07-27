# Contribution guidelines
- Code style example: https://gist.github.com/davidzchen/9187878

## Directories
- `src/cli` contains the rvm cli code (purely for interacting with the rvm library using a shell).
- `src/lib` contains the rvm library code (most rvm logic is here, compiled separately from the cli for using in other projects).
- `src/gen` contains the rvm bytecode generation library 
- `src/assembler` contains the readable bytecode to opcode translation library (used by the cli).
- `lib/` contains third-party libraries.
- `docs/` contains documentation :).
- `test/` contains tests.

## Sub-projects

### rvmcli - rvm cli
A cli tool for interacting with the rvm library.

Features:
- Run rvm bytecode files
- Run rvm readable bytecode files
- Run rvm bytecode from stdin
- Run rvm readable bytecode from stdin
- Translate rvm readable bytecode to rvm bytecode
- Translate rvm bytecode to rvm readable bytecode

### librvm - rvm library
The library for running rvm bytecode.

Features:
- Run rvm bytecode

### librvmgen - rvm bytecode generation library
A library for generating rvm bytecode.
This is used by compilers to generate rvm bytecode.

Features:
- API for generating rvm bytecode
- Option to generate rvm readable bytecode

### libras - translate from rvm assembly to rvm bytecode and vice versa
Does what it says on the tin. 

## File extensions
These are the standard file extensions for rvm files:
- `.rvm` is the extension for rvm bytecode files. 
- `.ras` is the extension for rvm readable bytecode files (assembly). 

The file extensions are optional, but they are recommended for clarity.

## Naming Conventions
1. All Macros, constants, and abbreviations in all caps: `MAX_STACK_SIZE`, `OPCODE_ENUM_LENGTH`, `VM`
2. Struct names and typedefs in UpperCamelCase: `InstructionBuffer`, `BytecodeTranslator`, `Stack`
3. Functions that operate on structs are classic C style: `push_stack`, `create_vm`
4. Struct fields, pointers, and variable names are classic C style: `foo`, `bar`, `max_capacity`
5. Global variables: nah just don't use these