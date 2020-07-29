#include "corewar.h"

int   put_exec_codeSize_in_cor(t_bot *bot, int fd)
{
  int   i;
  int   num;

  i = CHAMP_MAX_SIZE - bot->exec_code_size;
	if (i < 0)
		return (KO);
	num = 0;
  i = bot->exec_code_size;
	while ((i = i / 10))
		num++;
  num = 2 - num;
	while (num >= 0)
	{
		ft_putchar_fd('\0', fd);
		num--;
	}
	ft_putnbr_fd(bot->exec_code_size, fd);
  return (OK);
}
