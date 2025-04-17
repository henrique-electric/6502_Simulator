#include "../../include/cpu.h"

CPU init_new_cpu(void) {

    CPU new_cpu = {
        .register_a  = 0x00,
        .register_x  = 0x00,
        .register_y  = 0x00,
        .cpu_status  = 0x00,
        .register_sp = (uint8_t) STACK_END_ADDR_6502,
        .pc          = RAM_AND_ROM_ADDR_6502_START,
        .memory      = init_new_mem_6502()
    };
    set_up_instruction_array();
    return new_cpu;
}

uint16_t cast_uint16_uint8_addrs(uint8_t high_bytes, uint8_t low_bytes) {
    uint16_t fetched_addr = 0x0000;
    fetched_addr = (fetched_addr & 0x00FF) | (high_bytes << 8);
    fetched_addr = (fetched_addr & 0xFF00) | low_bytes;
    return fetched_addr;
}


void set_up_instruction_array(void) {
    instruction_handler[LDX_I]  = load_immediate_x;
    instruction_handler[LDY_I]  = load_immediate_y;
    instruction_handler[LDA_I]  = load_immediate_a;
    instruction_handler[LDA_AB] = load_absolute_a;
    instruction_handler[LDA_AX] = load_absolute_ax;
    instruction_handler[LDA_AY] = load_absolute_ay;
    instruction_handler[LDX_A]  = load_absolute_x; 
    instruction_handler[LDX_AY] = load_absolute_xy;
    instruction_handler[LDY_A]  = load_absolute_y;
    instruction_handler[LDY_AX] = load_absolute_yx;
    instruction_handler[LDA_Z]  = load_zero_page_a;
    instruction_handler[LDX_Z]  = load_zero_page_x;
    instruction_handler[LDY_Z]  = load_zero_page_y;
    instruction_handler[LDA_ZX] = load_zero_page_ax;
    instruction_handler[LDX_ZY] = load_zero_page_xy;
    instruction_handler[LDY_ZX] = load_zero_page_yx;

    instruction_handler[PHA]    = push_register_a;
    instruction_handler[PLA]    = pull_register_a;
    instruction_handler[PHP]    = push_flag_reg;
    instruction_handler[PLP]    = push_flag_reg;
}

// TODO -> implement clock
void fetch_instruction(CPU *cpu) {
    if (cpu == NULL)
        return;
    
    cpu->register_ir = memory_read_6502(&cpu->memory, cpu->pc);
    cpu->pc++;
    
}

void execute_6502(CPU *cpu) {
    if (cpu != NULL) {
        fetch_instruction(cpu);
        cpu->clock_count++;
        instruction_handler[cpu->register_ir](cpu);
    }
}

bool test_stack(CPU* cpu_ptr)
{
    if (cpu_ptr->register_sp == STACK_END_ADDR_6502) {
        cpu_ptr->memory.is_stack_full = true;
        return true;
    }
    return false;
}

void log_CPU_regs(CPU cpu)
{
    printf("A:    0x%x\n", cpu.register_a);
    printf("X:    0x%x\n", cpu.register_x);
    printf("Y:    0x%x\n", cpu.register_y);
    printf("SP:   0x%x\n", cpu.register_sp);
    printf("PC:   0x%x\n", cpu.pc);
    printf("Flag: 0x%b\n", cpu.cpu_status);
}

