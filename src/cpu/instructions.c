#include "../../include/cpu.h"

#define INSTRUCTION_ARGUMENT    cpu->pc + 1

#define get_zero_page_addr()    (memory_read_6502(&cpu->memory, cast_uint16_uint8_addrs(0x00, cpu->memory.virtual_memory[INSTRUCTION_ARGUMENT])))
#define get_zero_page_add_x()   (memory_read_6502(&cpu->memory, cast_uint16_uint8_addrs(0x00, cpu->memory.virtual_memory[INSTRUCTION_ARGUMENT]) + (uint16_t) cpu->register_x))
#define get_zero_page_add_y()   (memory_read_6502(&cpu->memory, cast_uint16_uint8_addrs(0x00, cpu->memory.virtual_memory[INSTRUCTION_ARGUMENT]) + (uint16_t) cpu->register_y))


// TODO -> implement clock
void load_immediate_x(CPU *cpu) {
    if (cpu != NULL) {
        cpu->register_x        = memory_read_6502(&cpu->memory, INSTRUCTION_ARGUMENT);
        cpu->pc += 2;
    }
}

// TODO -> implement clock
void load_immediate_y(CPU *cpu) {
    if (cpu != NULL) {
        cpu->register_y        = memory_read_6502(&cpu->memory, INSTRUCTION_ARGUMENT);
        cpu->pc += 2;
    }
}

// TODO -> implement clock
void load_immediate_a(CPU *cpu) {
    if (cpu != NULL) {
        cpu->register_a        = memory_read_6502(&cpu->memory, INSTRUCTION_ARGUMENT);
        cpu->pc += 2; 
    }
}

// TODO -> implement clock
void load_absolute_a(CPU *cpu) {
    if (cpu != NULL) {
        cpu->register_a        = memory_read_6502(&cpu->memory, (uint16_t) cpu->memory.virtual_memory[INSTRUCTION_ARGUMENT]);
        cpu->pc += 2;
    }
}

// TODO -> implement clock
void load_absolute_ax(CPU *cpu) {
    if (cpu != NULL) {
        cpu->register_a        = memory_read_6502(&cpu->memory, (uint16_t) cpu->memory.virtual_memory[INSTRUCTION_ARGUMENT] + cpu->register_x);
        cpu->pc += 2;
    }
}

// TODO -> implement clock
void load_absolute_ay(CPU *cpu) {
    if (cpu != NULL) {
        cpu->register_a        = memory_read_6502(&cpu->memory, (uint16_t) cpu->memory.virtual_memory[INSTRUCTION_ARGUMENT] + cpu->register_y);
        cpu->pc += 2;
    }
}

// TODO -> implement clock
void load_absolute_x(CPU *cpu) {
    if (cpu != NULL) {
        cpu->register_x       = memory_read_6502(&cpu->memory,  cpu->memory.virtual_memory[INSTRUCTION_ARGUMENT]);
        cpu->pc++;
    }
}

// TODO -> implement clock
void load_absolute_xy(CPU *cpu) {
    if (cpu != NULL) {
        cpu->register_x       = memory_read_6502(&cpu->memory, (uint16_t) cpu->memory.virtual_memory[INSTRUCTION_ARGUMENT] + cpu->register_y);
        cpu->pc += 2; 
    }
}

// TODO -> implement clock
void load_absolute_y(CPU *cpu) {
    if (cpu != NULL) {
        cpu->register_y      = memory_read_6502(&cpu->memory, cpu->memory.virtual_memory[INSTRUCTION_ARGUMENT]);
        cpu->pc += 2;
    }
}

// TODO -> implement clock
void load_absolute_yx(CPU *cpu) {
    if (cpu != NULL) {
        cpu->register_y     = memory_read_6502(&cpu->memory, (uint16_t) cpu->memory.virtual_memory[INSTRUCTION_ARGUMENT] + cpu->register_x);
        cpu->pc += 2;
    }
}

// TODO -> implement clock
void load_zero_page_a(CPU *cpu) {
    if (cpu != NULL) {
        cpu->register_a     = get_zero_page_addr();
        cpu->pc += 2;
    }
}

// TODO -> implement clock
void load_zero_page_x(CPU *cpu) {
    if (cpu != NULL) {
        cpu->register_x     = get_zero_page_addr();
        cpu->pc += 2;
    }
}

// TODO -> implement clock
void load_zero_page_y(CPU *cpu) {
    if (cpu != NULL) {
        cpu->register_y     = get_zero_page_addr();
        cpu->pc += 2;
    }
}

// TODO -> implement clock
void load_zero_page_ax(CPU *cpu) {
    if (cpu != NULL) {
        cpu->register_a     = get_zero_page_add_x();
        cpu->pc             += 2; 
    }
}

// TODO -> implement clock
void load_zero_page_xy(CPU *cpu) {
    if (cpu != NULL) {
        cpu->register_x     = get_zero_page_add_y();
        cpu->pc             += 2;
    }
}

void load_zero_page_yx(CPU *cpu) {
    if (cpu != NULL) {
        cpu->register_y     = get_zero_page_add_x();
        cpu->pc            += 2; 
    }
}


/*
    PUSH & PULL instructions
*/

void push_register_a(CPU *cpu) {
    if (cpu != NULL) {
        memory_write_6502(&cpu->memory, cpu->register_a, (uint16_t) cpu->register_sp);
        cpu->register_sp++;
    }
}

void pull_register_a(CPU *cpu) {
    if (cpu != NULL) {
        cpu->register_a       = memory_read_6502(&cpu->memory, (uint16_t) cpu->register_sp);
        cpu->register_sp--;
    }
}

void push_flag_reg(CPU *cpu) {
    if (cpu != NULL) {
        memory_write_6502(&cpu->memory, cpu->cpu_status, (uint16_t) cpu->register_sp);
        cpu->register_sp++;
    }
}                                 
                                  
void pull_flag_reg(CPU *cpu) {    
    if (cpu != NULL) {            
        cpu->cpu_status         = memory_read_6502(&cpu->memory, (uint16_t) cpu->register_sp);
        cpu->register_sp--;
    }
}