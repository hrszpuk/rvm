# Specification for RVM
RVM is a stack-based virtual machine.

# Architecture

## Stacks

### Value stack

### Call stack

## Instruction set
The instruction set will be 1 bytes large. This will be more than enough room for all the instructions we want.

The following are examples of instructions the VM may interpret:
``` 
halt            // Stop program
noop            // No operation

// Data operations
load            // Load data from local heap
gload           // Load data from global heap
store           // Store data onto local heap
gstore          // Store data onto global heap

push            // Push data onto stack
pop             // Pop data off stack
dup             // Duplicate top value on stack
swap            // Swap top two values on stack
const           // Push constant onto stack

// Arithmetric
// The following instructions pop two values off the stack and push the result onto the stack
add             // Add
sub             // Subtract
mul             // Multiply
div             // Divide
mod             // Modulo

// Bitwise
// The following instructions pop two values off the stack and push the result onto the stack
and             // Bitwise and
or              // Bitwise or
xor             // Bitwise xor
not             // Bitwise not
shl             // Bitwise shift left
shr             // Bitwise shift right

// Logicial
// The following instructions pop two values off the stack and push the result onto the stack
land            // Logical and
lor             // Logical or
lnot            // Logical not

// Comparisons
// The following instructions pop two values off the stack and push the result onto the stack
eq              // Equal
ne              // Not equal
lt              // Less than
le              // Less than or equal
gt              // Greater than
ge              // Greater than or equal

// Control flow
jmp             // Jump
jmpc            // Jump if condition (top of stack) is true or 1
call <name>     // Call subroutine
ret             // Return from function

// I/O
out           // Print single value
in            // Read single value

// Subroutines
begin <name>    // Begin subroutine
end             // End subroutine

// Loading other rvm scripts
preload <path>  // Load rvm script, NOTE: the order of the preload instructions is important
```

### Native types
The following are the native types that the VM will support:
- `i8` - [0-9] - 1 byte
- `i16` - [0-9] - 2 bytes
- `i32` - [0-9] - 4 bytes
- `i64` - [0-9] - 8 bytes
- `f32` - [0-9.] - 4 bytes
- `f64` - [0-9.] - 8 bytes
- `bool` - [0-1] - 1 byte
- `char` - [0-9a-zA-Z] - 1 byte
- `array` - [type\[size\]] - (size * sizeof(type)) bytes

### Macros
Macros are a way to extend the VM's instruction set. 
They are defined in the VM's bytecode and are translated into bytecode instructions by the translation library.
These instructions are not directly supported by the VM.

**Defining a macro**
``` 
macro <name> <args> {
    <instructions>
}

// Example
macro add3 {
    const 3
    addi
}

// Example with arguments
macro add {
    const <arg1>
    const <arg2>
    addi
}
```

**Using a macro**
``` 
<name>! <args>

// Example
add3!
add! 1 2
```

**Built-in macros**
``` 
repeat! <count> <instruction>
comment! <comment>
alias! <name> <instruction>
repeat_gen! <var> <count> <instruction> // Generates a repeat macro but replaces <var> with the current iteration
```

**Examples of built-in macros**
```
repeat! 2 const 1 // const 1 const 1
comment! "Hello World" // Does nothing
alias! add addi // add 1 2 -> addi 1 2, NOTE: this cannot override macros or instructions
repeat_gen! i 10 const <i> // const 0 const 1 const 2 const 3 const 4 const 5 const 6 const 7 const 8 const 9
```

## Using external rvm libraries
External rvm libraries provide pre-defined subroutines that can be utilised within your rvm program.
These libraries may be provided by the VM (via standard VM library) or by the user (via custom VM library).
This allows for libraries to be shared between programming languages.


# Resources
- https://dev.to/lexplt/understanding-bytecode-interpreters-eig
- https://dev.to/lexplt/parallelizing-a-bytecode-interpreter-58m8
- https://craftinginterpreters.com/