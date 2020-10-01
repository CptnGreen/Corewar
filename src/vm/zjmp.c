#include "corewar.h"

int		zjmp(t_vm *vm, t_process *process)
{
	if (process->carry == 1)
		process->pc += *(short*)(vm->arena + process->pc + 1) % IDX_MOD;
	return (OK);
}
