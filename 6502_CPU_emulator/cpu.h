#pragma once
#include "mem.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/*
  To makes things simple the names of some registers will be changed to make more easy to comment
  -------------------------------------------------------------------------------------------
  Accumulator Register		 == A
  X index Resgister			 == X
  Y index Register			 == Y
  Stack pointer register(SP) == SP
  CPU status flag register	 == CF
  Program Counter register	 == PC
  -------------------------------------------------------------------------------------------
  Zero Page		  = 0x0000 to 0x00FF
  Absolute value  = A value located at any address on the memory
  Immediate		  = A value which is described after the instruction 

*/

// Opcodes definitions
// Registers intruction opcodes
// Accumulator (A) register
#define LDA_I	0xA9	// Loads Immediate value to A Register
#define LDA_Z	0xA5	// Loads the value of a address value of Zero Page (0x00-0xFF) to A Register
#define LDA_ZX	0xB5	// Loads the value on a Zero Page memory address added to X register
#define LDA_A	0xAD	// Loads the value of a adress of the memory to A Register
#define LDA_AX	0xBD	// Access a memory address added to value of X register and load the value stored to A Register
#define LDA_AY  0xB9	// Aceess a memory Address added to value of Y register and Load the value stored to A register
#define LDA_IX	0xA1	// Access a memory address added with X register and load the value to A register
#define LDA_IY  0xB1	// Access a memory address added with Y register abd load the value to A register

// X index Register 
#define LDX_I	0xA2	// Loads a Immediate value to X register
#define LDX_Z	0xA6	// Loads the value on a address in Zero Page to X register 
#define LDX_ZY  0xB6	// Loads the value on a address added to Y register to X register
#define LDX_A	0xAE	// Loads a value stored in somewhere in the memory to X register
#define LDX_AY  0xBE	// loads a value stored in some address added with Y register to X register

// Y index Register
#define LDY_I	0xA0	// Loads the Immediate value to Y register
#define LDY_Z	0xA4	// Loads the value on zero page address to Y register
#define LDY_ZX  0xB4	// Access the memory address added to the value of X register and loads the value to Y register
#define LDY_A	0xAC	// Access a memory address and load its value to Y register
#define LDY_AX	0xBC	// Access a memory address added to X register value and loads the value to Y register


// Registers operation
#define TAX		0xAA	// Transfer the value on A register to X register
#define TXA		0x8A	// Transfer the value on X register to A register
#define	DEX		0xCA	// Decrement the value on X register
#define INX		0xE8	// Increment the value on X register
#define TAY		0xA8	// Transfer the value on A register to Y register
#define TYA		0x98	// Trasnfer the value on Y register to A register
#define DEY		0x88	// Decrement the value on Y register
#define INY		0xC8	// Increment the value on Y register


// Memory instruction opcodes
#define TXS	    0x9A	// Transfer the X register to SP resgister
#define TSX		0xBA	// Transfer the SP register to X register
#define PHA	    0x48	// Pushes to the stack the value stored on A register
#define PLA		0x68	// Pull the value stored on A register
#define PHP		0x08	// Pushes to the stack the CF register
#define PLP		0x28	// Pull the value of CF register stored on the stack

// Flag instruction
#define CLC		0x18	// Clear the carry bit on CF register
#define SEC		0x38	// Set carry bit on CF register
#define	CLI		0x58	// Clear the interrupt bit on CF register (Disable the interrupts) 
#define SEI		0x78	// Set interrupt bit on CF register
#define CLV		0xB8	// Clear overflow bit on CF register
#define CLD		0xD8	// Clear decimal bit on CF register
#define SED		0xF8	// Set decimal bit on CF register

// Logic instructions
#define ROL_A	0x2A	
#define ROL_Z	0x26
#define ROL_ZX	0x36
#define ROL_AB	0x2E
#define ROL_ABX 0x3E




typedef struct CPU {
	uint8_t      register_a;
	uint8_t      register_x;
	uint8_t      register_y;
	uint8_t      cpu_status;
	uint8_t      register_sp;
	uint16_t     pc;
	memory_6502  memory;
	uint64_t	 cycle_count;
} CPU;

CPU init_new_cpu();
bool test_stack(CPU* cpu_ptr);
void log_CPU_regs(CPU cpu);
void interpret_6502(CPU* cpu);
uint8_t get_op_cycle(uint8_t opcode);