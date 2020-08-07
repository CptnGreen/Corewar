#include "corewar.h"

int		check_extension(char *file_name)
{
	int		l;

	l = ft_strlen(file_name);
	if (l < 3 || \
		file_name[l - 1] != 's' || \
		file_name[l - 2] != '.')
		return (BAD_EXT);
	else
		return (l - 2);
}
