# include "corewar.h"

void  execute_instruction(t_vm *vm, t_process *process)
{
  if (process == "01" || process == "09" \
      || process == "0c" || process == "0f")
  {
    get_option_1(vm, process);
  }
  /*
  else if ((process + i == "01" || process + i == "09" \
      || process + i == "0c" || process + i == "0f"))
      */
}
