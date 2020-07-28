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
	//print_comment - needs to be checked
	ft_putstr_fd(bot->comment, fd);
	i = COMMENT_LENGTH - ft_strlen(bot->comment) + 4;
	while (i >= 0)
	{
		ft_putchar_fd('\0', fd);
		i--;
	}
	//
	//print_exec_code -nedds to be checked
	ft_putstr_fd(bot->exec_code, fd);
	//
	close(fd);//move in func that call print_byte_code
	return (OK);
}
