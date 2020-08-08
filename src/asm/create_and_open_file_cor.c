#include "corewar.h"

/*
** Called from print_byte_code()
*/

int		create_and_open_file_cor(int i, char *file_name, int log_fd)
{
	char	*name;
	int		fd;

	file_name[i] = '\0';
	name = ft_strjoin(name, ".cor");
	if (!(fd = open(name, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR)))
	{
		ft_putstr_fd("create_and_open_file_cor(): Something wrong\n",log_fd);
		return (KO);
	}
	ft_strdel(&name);
	ft_putstr_fd("create_and_open_file_cor(): Success\n",log_fd);
	return (fd);
}
