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