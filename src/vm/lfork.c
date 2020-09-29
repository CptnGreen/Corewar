#include "corewar.h"

void    lfork(t_vm *vm, t_process *process)
{
  t_process   new_process;

  new_process = (t_process*)malloc(sizeof(t_process));
  memcpy(new_process, process, sizeof(t_process));
  //memcpy(new_process->registries, process->registries, sizeof(process->registries));
  //memcpy(new_process->carry, process->carry, sizeof(process->carry));
  process->pc = process->pc + (process->pc + 1);//check
}
