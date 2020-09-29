#include "corewar.h"

void  fork(t_vm *vm, t_process *process)
{
  t_process   new_process;

  new_process = (t_process*)malloc(sizeof(t_process));
  if (new_process)
  {
    memcpy(new_process, process, sizeof(t_process));
   // memcpy(new_process->registries, process->registries, sizeof(process->registries)); 
   // memcpy(new_process->carry, process->carry, sizeof(process->carry)); 
    process->pc = process->pc + ((process->pc + 1) % IDX_MOD);//check
  }
}
