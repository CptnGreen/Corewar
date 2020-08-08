#include "corewar.h"

/*
** Called from print_byte_code()
*/

int			put_exec_code_size_in_cor(t_bot *bot, int fd, int log_fd)
{
	int		i;
	char		*res;

	i = 3;
	res = (char*)(&bot->exec_code_size);
	while (i >= 0)
	{
		ft_putchar_fd(res[i], fd);
		i--;
	}
	ft_putstr_fd("put_exec_code_size_in_cor(): Success\n", log_fd);
	return (OK);
}
