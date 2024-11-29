#include "../../include/cpu.h"
#define INSTRUCTION_ARGUMENT    cpu->pc + 1

#define get_zero_page_addr()    (memory_read_6502(&cpu->memory, cast_uint16_uint8_addrs(0x00, cpu->memory.virtual_memory[INSTRUCTION_ARGUMENT])))


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

void load_zero_page_x(CPU *cpu) {
    if (cpu != NULL) {
        cpu->register_x     = get_zero_page_addr();
        cpu->pc += 2;
    }
}
