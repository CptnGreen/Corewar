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
    lseek(fd, 0, SEEK_END);
    ft_putstr_fd(get_magic_header(), fd);
    ft_putstr_fd(bot->name, fd);
	i = PROG_NAME_LENGTH - ft_strlen(bot->name) + 4;
	while (i >= 0)
	{
		ft_putchar_fd('\0', fd);
		i--;
	}
	close(fd);
	return (OK);
}
