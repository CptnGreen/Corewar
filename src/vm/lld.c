#include "corewar.h"

void    lld(t_vm *vm, t_process *process)
{
    if (process + 1 == '90')
        process->registries[int(process + 2)] = process + 2;
    else if (process->pc + 1 == 'D0')
       process->registries[int(process + 5)] = (int)(process); 
    if (process->registries[(int)(process + 2)] = 0)
        process->carry = 1;
    else
        process->carry = 0;
}