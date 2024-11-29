#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#define MEMORY_LOG_ARRAY_LEN                      256

#define MAX_MEMORY_LEN                            0xFFFF

// Stack memory adresses
#define STACK_START_ADDR_6502                     0x0100
#define STACK_END_ADDR_6502                       0x01FF

// Reserved system RAM addresses
#define SYSTEM_RAM_REGION_AND_IO_ADDR_6502_START  0x0200
#define SYSTEM_RAM_REGION_AND_IO_ADDR_6502_END    0x7FFF
#define SYSTEM_RAM_REGION_AND_IO_ADDR_6502_OFFSET 0x7FFF - 0x0200

// RAM and ROM memory addresses
#define RAM_AND_ROM_ADDR_6502_START               0x8000
#define RAM_AND_ROM_ADDR_6502_END                 0xFFFF
#define RAM_AND_ROM_ADDR_6502_OFFSET RAM_AND_ROM_ADDR_6502_END - RAM_AND_ROM_ADDR_6502_START



#define LOCK_ADDR_ACTION 0
#define FREE_ADDR_ACTION 1

typedef struct memory_6502 {
    uint8_t virtual_memory[MAX_MEMORY_LEN];
    bool is_addr_free[MAX_MEMORY_LEN];
    uint16_t bits_loaded_to_mem;
    uint16_t available_addrs;
    bool is_stack_full;
} memory_6502;

memory_6502 init_new_mem_6502(void);
uint8_t memory_read_6502(const memory_6502 *memory_struct, uint16_t addr);
void    memory_write_6502(memory_6502* memory_struct, uint8_t data, uint16_t addr);
void    push_log_6502(memory_6502* memory_struct, const char* log_msg);
bool    load_bin_to_mem_6502(memory_6502* memory_struct, const uint8_t* opcodes, uint16_t bin_size);
void    change_mem6502_addr_state(memory_6502* memory_struct, uint16_t addr, uint8_t action);
void    log_mem(memory_6502 memory_struct);
