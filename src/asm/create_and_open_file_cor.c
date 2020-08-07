#include "corewar.h"

int		create_and_open_file_cor(int i, char *file_name)
{
	char	*name;
	int		fd;

	file_name[i] = '\0';
	name = ft_strjoin(name, ".cor");
	if (!(fd = open(name, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR)))
		return (KO);
	ft_strdel(&name);
	return (fd);
}
