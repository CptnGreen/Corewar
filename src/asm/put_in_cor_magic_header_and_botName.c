#include "corewar.h"

void    put_in_cor_magic_header_and_botName(int fd, t_bot *bot)
{
  int   i;

  lseek(fd, 0, SEEK_END);
  ft_putstr_fd(get_magic_header(), fd);
  ft_putstr_fd(bot->name, fd);
	i = PROG_NAME_LENGTH - ft_strlen(bot->name) + 4;
	while (i >= 0)
	{
		ft_putchar_fd('\0', fd);
		i--;
	}
}
