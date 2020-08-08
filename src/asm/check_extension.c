#include "corewar.h"

/*
** Called from print_byte_code()
*/

int		check_extension(char *file_name, int log_fd)
{
	int		l;

	l = ft_strlen(file_name);
	if (l < 3 || \
		file_name[l - 1] != 's' || \
		file_name[l - 2] != '.')
	{
		ft_putstr_fd("check_extension(): bad extension\n", log_fd);
		return (BAD_EXT);
	}
	else
	{
		ft_putstr_fd("check_extension(): found \".s\" at the end of file name\n", log_fd);
		return (l - 2);
	}
}
