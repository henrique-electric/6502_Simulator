#pragma once
#include "mem.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#define CARRY_BIT                 (1 << 0)   // Indicates the status of the carry bit
#define ZERO_BIT                  (1 << 1)   // Indicates the some instruction resulted in zero
#define INT_BIT                   (1 << 2)   // Indicates if the interrupts are enabled
#define DECIMAL_BIT               (1 << 3)   // Is set to use binary-coded-decimal to easy make base 10 aritmetic
#define B_FLAG_BIT                (1 << 4)   //
#define BIT_1                     (1 << 5) // Always set to 1, :(
#define OVERFLOW_BIT              (1 << 6)   // Indicates if a overflow happend on a register
#define NEGATIVE_BIT              (1 << 7)   // Indicates if a number is negative

#define CPU_CLOCK                 0.0000001

#define TOTAL_NUMBER_INSTRUCTIONS 0xFF

// Data type defines..... just for help on intellisense on vscode

/*
  To makes things simple the names of some registers will be changed to make more easy to comment
  -------------------------------------------------------------------------------------------
  Accumulator Register           == A
  X index Resgister              == X
  Y index Register               == Y
  Stack pointer register(SP)     == SP
  CPU status flag register       == CF
  Program Counter register       == PC
  -------------------------------------------------------------------------------------------
  Zero Page            = 0x0000 to 0x00FF
  Absolute value  = A value located at any address on the memory
  Immediate            = A value which is described after the instruction
 
 "lsb_storage" is used to store least significant bytes
 "msb_storage" is used to store high significant bytes
*/

// Load instruction constants opcodes
enum load_registers_opcodes{
  // Acummulator register LD instuctions
  LDA_I   = 0xA9,     // Loads Immediate value to A Register
  LDA_Z   = 0xA5,     // Loads the value of a address value of Zero Page (0x00-0xFF) to A Register
  LDA_ZX  = 0xB5,     // Loads the value on a Zero Page memory address added to X register
  LDA_AB  = 0xAD,     // Loads the value of a adress of the memory to A Register
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
};

// Memory instruction opcodes enum
enum memory_instruction_opcodes{
  PHA     = 0x48,     // Pushes to the stack the value stored on A register
  PLA     = 0x68,     // Pull the value stored on A register
  PHP     = 0x08,     // Pushes to the stack the CF register
  PLP     = 0x28      // Pull the value of CF register stored on the stack
};

// Registers instructions opcodes enum
enum register_operation_opcodes{
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
};

enum flag_register_opcodes{
  CLC     = 0x18,      // Clear the carry bit on CF register
  SEC     = 0x38,      // Set carry bit on CF register
  CLI     = 0x58,      // Clear the interrupt bit on CF register (Disable the interrupts)
  SEI     = 0x78,      // Set interrupt bit on CF register
  CLV     = 0xB8,      // Clear overflow bit on CF register
  CLD     = 0xD8,      // Clear decimal bit on CF register
  SED     = 0xF8       // Set decimal bit on CF register
};


// Logic instuctions opcodes enum
enum logic_instructions_opcodes{
  ROL_A   = 0x2A,
  ROL_Z   = 0x26,
  ROL_ZX  = 0x36,
  ROL_AB  = 0x2E,
  ROL_ABX = 0x3E,
  
  ROR_A   = 0x6A,
  ROR_Z   = 0x66,
  ROR_ZX  = 0x76,
  ROR_AB  = 0x6E,
  ROR_ABX = 0x7E,

  ORA_I   = 0x09,
  ORA_Z   = 0x05,
  ORA_ZX  = 0x15,
  ORA_AB  = 0x0D,
  ORA_ABX = 0x1D,
  ORA_ABY = 0x19,
  ORA_INX = 0x01,
  ORA_INY = 0x11,

  CMP_I   = 0xC9,
  CMP_Z   = 0xC5,
  CMP_ZX  = 0xD5,
  CMP_AB  = 0xCD,
  CMP_ABX = 0xDD,
  CMP_ABY = 0xD9,
  CMP_INX = 0xC1,
  CMP_INY = 0xD1,

  CPX_I   = 0xE0,
  CPX_Z   = 0xE4,
  CPX_AB  = 0xEC,

  CPY_I   = 0xC0,
  CPY_Z   = 0xC4,
  CPY_AB  = 0xCC,
}; // TODO

enum code_flow_control {
  RTI     = 0x40,
  RTS     = 0x60,
};

enum arithmetic_logic_opcodes {
  SBC_I   = 0xE9,
  SBC_Z   = 0xE5,
  SBC_ZX  = 0xF5,
  SBC_AB  = 0xED,
  SBC_ABX = 0xFD,
  SBC_ABY = 0xF9,
  SBC_INX = 0xE1,
  SBC_INY = 0xF1,

  ADC_I   = 0x69,
  ADC_Z   = 0x65,
  ADC_ZX  = 0x75,
  ADC_AB  = 0x6D,
  ADC_ABX = 0x7D,
  ADC_ABY = 0x79,
  ABC_INX = 0x61,
  ABC_INY = 0x71,

  ASL_A   = 0x0A,
  ASL_Z   = 0x06,
  ASL_ZX  = 0x16,
  ASL_AB  = 0x0E,
  ASL_ABX = 0x1E
};



typedef struct CPU {
    uint8_t      register_a, register_x, register_y, cpu_status, register_sp, register_ir, lsb_storage, msb_storage;
    uint16_t     pc;
    int clock_count;
    memory_6502  memory;
} CPU;

void load_immediate_x (CPU  *cpu);
void load_immediate_y (CPU  *cpu);
void load_immediate_a (CPU  *cpu);

void load_absolute_a  (CPU  *cpu);
void load_absolute_x  (CPU  *cpu);
void load_absolute_ax (CPU  *cpu);
void load_absolute_ay (CPU  *cpu);
void load_absolute_xy (CPU  *cpu);
void load_absolute_y  (CPU  *cpu);
void load_absolute_yx (CPU  *cpu);

void load_zero_page_a (CPU  *cpu);
void load_zero_page_x (CPU  *cpu);
void load_zero_page_y (CPU  *cpu);
void load_zero_page_ax(CPU  *cpu);
void load_zero_page_xy(CPU  *cpu);
void load_zero_page_yx(CPU  *cpu);

void push_register_a  (CPU  *cpu);
void pull_register_a  (CPU  *cpu);
void push_flag_reg    (CPU  *cpu);
void pull_flag_reg    (CPU  *cpu);




void set_up_instruction_array(void);
void (*instruction_handler[TOTAL_NUMBER_INSTRUCTIONS])(CPU *cpu);
void fetch_instruction(CPU *cpu);
CPU init_new_cpu(void);
bool test_stack(CPU* cpu_ptr);
void log_CPU_regs(CPU cpu);
void interpret_6502(CPU* cpu);
void execute_6502(CPU *cpu);
uint16_t cast_uint16_uint8_addrs(uint8_t high_bytes, uint8_t low_bytes);
uint8_t get_op_cycle(uint8_t opcode);

