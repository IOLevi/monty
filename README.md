# Holberton School - Stacks, Queues - LIFO, FIFO
# Monty ByteCode Interpreter

## The Monty Language
Monty 0.98 is a scripting language that is first compiled into Monty byte codes (Just like Python). It relies on a unique stack, with specific instructions to manipulate it. The goal of this project is to create an interpreter for Monty ByteCodes files.

## Compilation
``gcc -Wall -Werror -Wextra -pedantic *.c -o monty``

## Usage
#### ex: ``./monty <bytecode>``
The bytecode file contains lines of opcode.
#### List of opcodes:
0. `push` - pushes an element to the stack
1. `pall` - prints all the values on the stack, starting from the top of the stack
2. `pint` - prints the value at the top of the stack
3. `pop` - removes the top element of the stack
4. `swap` - swaps the top two elements of the stack
5. `add` - adds the top two elements of the stack
6. `nop` - doesn't do anything
7. `sub` - subtracts the top element of the stack from the second top element of the stack
8. `div` - divides the second top element of the stack by the top element of the stack
9. `mul` - multiples the second top element of the stack with the top element of the stack
10. `mod` - computes the rest of the division of the second top element of the stack by the top element of the stack
11. `pchar` - prints the char at the top of the stack
12. `pstr` - prints the string at the top of the stack

## Authors
* **Evan Sznol** [GitHub](github.com/IOlevi)
* **Anthony la'O** [GitHub](github.com/amlao)
