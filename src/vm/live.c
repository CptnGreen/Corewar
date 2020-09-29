#include "corewar.h"

void  live(t_vm *vm, t_process *process)
{
  process->alive = 1;
  if ((int)(process + 1) == process->registers[0])
    vm->survivor = process->registries[0];
}
