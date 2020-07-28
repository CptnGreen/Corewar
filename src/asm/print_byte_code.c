#include "corewar.h"

int		print_byte_code(char *file_name, t_bot *bot)
{
	int   fd;
	int   i;
	char  *name;

	i = check_extension(file_name);
	if ((i = check_extension(file_name)) == -2)
		return (KO);
	if ((fd = create_and_open_file_cor(i, name, file_name)) == -1)
		return (KO);
	put_in_cor_magic_header_and_botName(fd, bot);
	i = put_exec_codeSize_in_cor(bot, fd); //needs to be checked
	if (i == KO)
		return (KO);
	close(fd);//move in func that call print_byte_code
	return (OK);
}
