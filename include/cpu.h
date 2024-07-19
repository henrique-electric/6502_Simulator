#pragma once
#include "mem.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

// Data type defines..... just for help on intellisense on vscode


/*
  To makes things simple the names of some registers will be changed to make more easy to comment
  -------------------------------------------------------------------------------------------
  Accumulator Register		   == A
  X index Resgister			     == X
  Y index Register			     == Y
  Stack pointer register(SP) == SP
  CPU status flag register	 == CF
  Program Counter register	 == PC
  -------------------------------------------------------------------------------------------
  Zero Page		    = 0x0000 to 0x00FF
  Absolute value  = A value located at any address on the memory
  Immediate		    = A value which is described after the instruction 

*/

// Load instruction constants opcodes
enum {
  // Acummulator register LD instuctions
  LDA_I   = 0xA9,     // Loads Immediate value to A Register
  LDA_Z   = 0xA5,     // Loads the value of a address value of Zero Page (0x00-0xFF) to A Register
  LDA_ZX  = 0xB5,     // Loads the value on a Zero Page memory address added to X register
  LDA_A   = 0xAD,     // Loads the value of a adress of the memory to A Register
  LDA_AX  = 0xBD,     // Access a memory address added to value of X register and load the value stored to A Register
  LDA_AY  = 0xB9,     // Aceess a memory Address added to value of Y register and Load the value stored to A register
  LDA_IX  = 0xA1,     // Access a memory address added with X register and load the value to A register
  LDA_IY  = 0xB1,     // Access a memory address added with Y register abd load the value to A register
  

  // X index register LD instructions
  LDX_I   = 0xA2,     // Loads a Immediate value to X register
  LDX_Z   = 0xA6,     // Loads the value on a address in Zero Page to X register 
  LDX_ZY  = 0xB6,     // Loads the value on a address added to Y register to X register
  LDX_A   = 0xAE,     // Loads a value stored in somewhere in the memory to X register
  LDX_AY  = 0xBE,     // loads a value stored in some address added with Y register to X register

  // Y index register LD instructions
  LDY_I   = 0xA0,     // Loads the Immediate value to Y register
  LDY_Z   = 0xA4,     // Loads the value on zero page address to Y register
  LDY_ZX  = 0xB4,     // Access the memory address added to the value of X register and loads the value to Y register
  LDY_A   = 0xAC,     // Access a memory address and load its value to Y register
  LDY_AX  = 0xBC,     // Access a memory address added to X register value and loads the value to Y register
} load_registers_opcodes;

// Memory instruction opcodes enum
enum {

  PHA     = 0x48,     // Pushes to the stack the value stored on A register
  PLA     = 0x68,     // Pull the value stored on A register
  PHP     = 0x08,     // Pushes to the stack the CF register
  PLP     = 0x28      // Pull the value of CF register stored on the stack
} memory_instruction_opcodes;

// Registers instructions opcodes enum
enum {
  TAX     = 0xAA,     // Transfer the value on A register to X register
  TAY     = 0xA8,     // Transfer the value on A register to Y register
  TXA     = 0x8A,     // Transfer the value on X register to A register
  TYA     = 0x98,     // Transfer the value on Y register to A register
  TXS     = 0x9A,     // Transfer the X register to SP resgister
  TSX     = 0xBA,     // Transfer the SP register to X register
  DEX     = 0xCA,     // Decrement the value on X register
  INX     = 0xE8,     // Increment the value on X register
  DEY     = 0x88,     // Decrement the value on Y register
  INY     = 0xC8,     // Increment the value on Y register
} register_operation_opcodes;

enum {
  CLC     = 0x18,      // Clear the carry bit on CF register
  SEC     = 0x38,      // Set carry bit on CF register
  CLI     = 0x58,      // Clear the interrupt bit on CF register (Disable the interrupts)
  SEI     = 0x78,      // Set interrupt bit on CF register
  CLV     = 0xB8,      // Clear overflow bit on CF register
  CLD     = 0xD8,      // Clear decimal bit on CF register
  SED     = 0xF8       // Set decimal bit on CF register
} flag_register_opcodes;


// Logic instuctions opcodes enum

enum {
  ROL_A   = 0x2A,
  ROL_Z   = 0x26,
  ROL_ZX  = 0x36,
  ROL_AB  = 0x2E,
  ROL_ABX = 0x3E
} logic_instructions_opcodes; // TODO

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