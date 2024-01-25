# Contribution guidelines
- Code style example: https://gist.github.com/davidzchen/9187878

## Directories
- `src/cli` contains the rvm cli code (purely for interacting with the rvm library using a shell).
- `src/lib` contains the rvm library code (most rvm logic is here, compiled separately from the cli for using in other projects).
- `src/gen` contains the rvm bytecode generation library 
- `src/tra` contains the readable bytecode to opcode translation library (used by the cli & lib).
- `lib/` contains third-party libraries.
- `docs/` contains documentation :).
- `test/` contains tests.

## Sub-projects

### rvm - rvm cli
A cli tool for interacting with the rvm library.

Features:
- [ ] Run rvm bytecode files
- [ ] Run rvm readable bytecode files
- [ ] Run rvm bytecode from stdin
- [ ] Run rvm readable bytecode from stdin
- [ ] Translate rvm readable bytecode to rvm bytecode
- [ ] Translate rvm bytecode to rvm readable bytecode

### librvm - rvm library
The library for running rvm bytecode.

Features:
- [ ] Run rvm bytecode

### librvmgen - rvm bytecode generation library
A library for generating rvm bytecode.
This is used by compilers to generate rvm bytecode.

Features:
- [ ] API for generating rvm bytecode
- [ ] Option to generate rvm readable bytecode
