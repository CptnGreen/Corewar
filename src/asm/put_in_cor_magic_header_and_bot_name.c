#include "corewar.h"

#define N_DIV_ZEROES 3

/*
** Called from print_byte_code()
*/

void		put_in_cor_magic_header_and_bot_name(int fd, t_bot *bot, int log_fd)
{
	int		i;

	ft_putstr_fd(get_magic_header(), fd);
	ft_putstr_fd(bot->name, fd);
	i = PROG_NAME_LENGTH - ft_strlen(bot->name) + N_DIV_ZEROES;
	while (i >= 0)
	{
		ft_putchar_fd('\0', fd);
		i--;
	}
	ft_putstr_fd("put_in_cor_magic_header_and_bot_name(): finished\n", log_fd);
	return ;
}
