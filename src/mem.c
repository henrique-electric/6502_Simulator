#include "../include/mem.h"


memory_6502 init_new_mem_6502(void) {
    memory_6502 new_mem_Struct;
    memset(new_mem_Struct.virtual_memory, 0x00, MAX_MEMORY_LEN);
    memset(new_mem_Struct.is_addr_free, true, MAX_MEMORY_LEN);
    new_mem_Struct.bits_loaded_to_mem = 0x0000;
    new_mem_Struct.is_stack_full = false;
    new_mem_Struct.available_addrs = 0xFFFF;
    return new_mem_Struct;
}

uint8_t memory_read_6502(const memory_6502 *memory_struct, uint16_t addr) {
    return memory_struct->virtual_memory[addr];
}

void memory_write_6502(memory_6502* memory_struct, uint8_t data, uint16_t addr) {
    if (memory_struct != NULL) {
        if (memory_struct->is_addr_free[addr] == true) {
            memory_struct->virtual_memory[addr] = data;
            memory_struct->available_addrs--;
            memory_struct->is_addr_free[addr] = false;
        }
    }
}


bool load_bin_to_mem_6502(memory_6502* memory_struct, const uint8_t* opcodes, uint16_t bin_size) {

    if (memory_struct != NULL && opcodes != NULL)
    {
        uint16_t ram_addr_count = RAM_AND_ROM_ADDR_6502_START;
        for (uint16_t opcode_index = 0x0000; opcode_index < bin_size && opcode_index < RAM_AND_ROM_ADDR_6502_OFFSET; opcode_index++)
        {
            memory_write_6502(memory_struct, opcodes[opcode_index], ram_addr_count);
            memory_struct->bits_loaded_to_mem++;
            ram_addr_count++;
        }
        return true;
    }
    return 0;
}


void change_mem6502_addr_state(memory_6502* memory_struct, uint16_t addr, uint8_t action) {
    if (addr >= 0 && addr <= MAX_MEMORY_LEN) {
        switch (action) {
          case LOCK_ADDR_ACTION:
              memory_struct->is_addr_free[addr] = false;
              break;

          case FREE_ADDR_ACTION:
              memory_struct->is_addr_free[addr] = true;
              break;

          default:
              break;
        }
    }
}
