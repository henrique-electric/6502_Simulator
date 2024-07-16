#include "cpu.h"

int main()
{
	CPU cpu_6502 = init_new_cpu();

	memory_write_6502(&cpu_6502.memory, 0xB2, 0xBFBA);
	log_mem(cpu_6502.memory);
	return 0;
}