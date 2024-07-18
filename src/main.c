#include "../include/cpu.h"

int main()
{
	CPU new_cpu = init_new_cpu();
	log_CPU_regs(new_cpu);
	return 0;
}