#include "corewar.h"

int		check_extension(char *file_name)
{
	int	i;

	i = ft_strlen(file_name);
	i--;
	if (file_name[i] == 's')
		i--;
	else
		return (-2);
	if (file_name[i] == '.')
		i--;
	else
		return (-2);
	return (i);
}
