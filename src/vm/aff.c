#include "corewar.h"

void  aff(t_vm *vm, t_process *process)
{
  char    s;

  s = (char)process->registers[process->pc + 1];
  ft_putnbr(s);
}
