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


static void set_up_instruction_array(void) {
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
}

// TODO -> implement clock
uint8_t fetch_instruction(CPU *cpu) {
    if (cpu == NULL)
        return 0x0000;
    
    return memory_read_6502(&cpu->memory, cpu->pc);
}

void execute_6502(CPU *cpu) {
    if (cpu != NULL) {
        uint8_t current_instruction = fetch_instruction(cpu);
        usleep(1);
        instruction_handler[current_instruction](cpu);
    }
}

// TODO -> #REMOVE THIS FUNCTION
/*
void interpret_6502(CPU* cpu_ptr) {
    if (cpu_ptr != NULL) {
        uint8_t opcode           = 0x00;
        uint8_t arg1             = 0x00;
        uint8_t arg2             = 0x00;
        uint8_t arg3             = 0x00;
        uint16_t absolute_value  = 0x0000;
        for (uint16_t count = 0; count < cpu_ptr->memory.bits_loaded_to_mem; count++) {

            opcode = cpu_ptr->pc; 
            switch (opcode) {
                case LDA_I:
                    cpu_ptr->register_a = (cpu_ptr->pc & 0x00FF); // Gets the lower bits from the instruction, because the instruction needs a argument
                    cpu_ptr->pc++;
                    usleep(1);
                    break;

                case LDA_AB:
                    cpu_ptr->register_a = memory_read_6502(cpu_ptr->memory, absolute_value);
                    break;

                case LDA_AX:
                    cpu_ptr->register_a = memory_read_6502(cpu_ptr->memory, absolute_value + (uint16_t) cpu_ptr->register_x);
                    break;

                case LDA_AY:
                    cpu_ptr->register_a = memory_read_6502(cpu_ptr->memory, absolute_value + (uint16_t) cpu_ptr->register_y);
                    break;

                case LDX_I:
                    cpu_ptr->register_x = arg1;
                    break;

                case LDY_I:
                    cpu_ptr->register_y = arg1;
                    break;

                case INX:
                    cpu_ptr->register_x++;
                    break;

                case INY:
                    cpu_ptr->register_y++;
                    break;
                    
                case CLC:
                    cpu_ptr->cpu_status &= ~(1 << CARRY_BIT);
                    break;
                    
                case SEC:
                    cpu_ptr->cpu_status |= (1 << CARRY_BIT);
                    break;
                    
                case CLI:
                    cpu_ptr->cpu_status &= ~(1 << INT_BIT);
                    cpu_ptr->pc++;
                    break;
                
                case SEI:
                    cpu_ptr->cpu_status |= (1 << INT_BIT);
                    cpu_ptr->pc++;
                    break;
                    
                case CLV:
                    cpu_ptr->cpu_status &= ~(1 << OVERFLOW_BIT);
                    cpu_ptr->pc++;
                    break;
                    
                case CLD:
                    cpu_ptr->cpu_status &= ~(1 << DECIMAL_BIT);
                    cpu_ptr->pc++;
                    break;
                    
                case SED:
                    cpu_ptr->cpu_status |= (1 << DECIMAL_BIT);
                    cpu_ptr->pc++;
                    break;
                    
                case PHA:
                    
                    if (!test_stack(cpu_ptr)) {
                        memory_write_6502(&cpu_ptr->memory, cpu_ptr->register_a, (uint16_t) cpu_ptr->register_sp);
                        cpu_ptr->register_sp--;
                        cpu_ptr->pc++;
                    }
                    break;
                    
                case PLA:
                    
                    if (!test_stack(cpu_ptr)) {
                        cpu_ptr->register_a = memory_read_6502(cpu_ptr->memory, (uint16_t) cpu_ptr->register_sp);
                        change_mem6502_addr_state(&cpu_ptr->memory, (uint16_t) cpu_ptr->register_sp, FREE_ADDR_ACTION);
                        cpu_ptr->register_sp++;
                        cpu_ptr->pc++;
                    }
                    break;
                
                case PHP:
                    
                    if (!test_stack(cpu_ptr)) {
                        memory_write_6502(&cpu_ptr->memory, cpu_ptr->cpu_status, (uint16_t) cpu_ptr->register_sp);
                        cpu_ptr->register_sp--;
                        cpu_ptr->pc++;
                    }
                    break;
                    
                case PLP:
                    
                    if (!test_stack(cpu_ptr)) {
                        cpu_ptr->cpu_status = memory_read_6502(cpu_ptr->memory, (uint16_t) cpu_ptr->register_sp);
                        change_mem6502_addr_state(&cpu_ptr->memory, (uint16_t) cpu_ptr->register_sp, FREE_ADDR_ACTION);
                        cpu_ptr->register_sp++;
                        cpu_ptr->pc++;
                    }
                    break;
                    
                case TAX:
                    cpu_ptr->register_x = cpu_ptr->register_a;
                    cpu_ptr->pc++;
                    break;
                    
                case TAY:
                    cpu_ptr->register_y = cpu_ptr->register_a;
                    cpu_ptr->pc++;
                    break;
                    
                case TXA:
                    cpu_ptr->register_a = cpu_ptr->register_x;
                    cpu_ptr->pc++;
                    break;
                    
                case TYA:
                    cpu_ptr->register_a = cpu_ptr->register_y;
                    cpu_ptr->pc++;
                    break;
                    
                case TXS:
                    cpu_ptr->register_sp = cpu_ptr->register_x;
                    cpu_ptr->pc++;
                    break;
                    
                case TSX:
                    cpu_ptr->register_x = cpu_ptr->register_sp;
                    cpu_ptr->pc++;
                    break;
            default:
                break;
            }

        }
    }
}
*/

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
    printf("Flag: 0x%b\n", cpu.cpu_status);
}

