#include "cpu.h"


CPU init_new_cpu() {
    CPU new_cpu = {
        .cpu_status  = 0x00,
        .register_a  = 0x00,
        .register_x  = 0x00,
        .register_y  = 0x00,
        .pc          = RAM_AND_ROM_ADDR_6502_START,
        .register_sp = STACK_END_ADDR_6502,
        .memory      = init_new_mem_6502()
    };
    return new_cpu;
}


void interpret_6502(CPU* cpu_ptr) {
    if (cpu_ptr != NULL) {
        uint8_t opcode = 0x00;
        uint8_t arg1 = 0x00;
        uint8_t arg2 = 0x00;
        uint8_t arg3 = 0x00;

        for (uint16_t count = 0; count < cpu_ptr->memory.bits_loaded_to_mem; count++) {

            opcode = cpu_ptr->memory.virtual_memory[cpu_ptr->pc];
            arg1 = cpu_ptr->memory.virtual_memory[cpu_ptr->pc + 1];
            arg2 = cpu_ptr->memory.virtual_memory[cpu_ptr->pc + 2];
            arg3 = cpu_ptr->memory.virtual_memory[cpu_ptr->pc + 3];

            switch (opcode) {
            case LDA_I:
                cpu_ptr->register_a = arg1;
                cpu_ptr->pc += 2;
                cpu_ptr->cycle_count += 2;
                break;

            case LDX_I:
                cpu_ptr->register_x = arg1;
                cpu_ptr->pc += 2;
                cpu_ptr->cycle_count += 2;
                break;

            case LDY_I:
                cpu_ptr->register_y = arg1;
                cpu_ptr->pc += 2;
                cpu_ptr->cycle_count += 2;
                break;

            case INX:
                cpu_ptr->register_x++;
                cpu_ptr->pc++;
                cpu_ptr->cycle_count++;
                break;

            case INY:
                cpu_ptr->register_y++;
                cpu_ptr->pc++;
                cpu_ptr->cycle_count++;
                break;
            default:
                break;
            }

        }
    }
}

bool test_stack(CPU* cpu_ptr)
{
    if (cpu_ptr->register_sp == STACK_START_ADDR_6502)
    {
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
    printf("Flag: 0x%x\n", cpu.cpu_status);
}
