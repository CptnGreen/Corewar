#include "corewar.h"

int		print_byte_code(char *file_name, t_bot *bot)
{
	int   fd;
	int   i;
	char  *name;

	//check file
	i = check_extension(file_name);
	if (i == -2)
		return (KO);
	//create and open file
	fd = create_and_open_file_cor(i, name, file_name);
	if (fd == -1)
		return (KO);
	//etc
	close(fd);
	return (OK);
}
