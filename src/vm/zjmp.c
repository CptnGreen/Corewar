#include "corewar.h"

void  zjmp(t_vm *vm, t_process *process)
{
  if (process->carry == 1)
      process->pc = (int)(process) + (((int)process + 1) % IDX_MOD);
}
