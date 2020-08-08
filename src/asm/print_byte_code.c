#include "corewar.h"

#define N_DIV_ZEROES 3

/*
** Called from main()
*/

int		print_byte_code(char *file_name, t_bot *bot, int log_fd)
{
	int		fd;
	int		i;

	if ((i = check_extension(file_name, log_fd)) == BAD_EXT || \
		(fd = create_and_open_file_cor(i, file_name, log_fd)) == -1)
		return (KO);
	put_in_cor_magic_header_and_bot_name(fd, bot, log_fd);
	i = put_exec_code_size_in_cor(bot, fd, log_fd);
	if (i == KO)
		return (KO);
	ft_putstr_fd(bot->comment, fd);
	i = COMMENT_LENGTH - ft_strlen(bot->comment) + N_DIV_ZEROES;
	while (i >= 0)
	{
		ft_putchar_fd('\0', fd);
		i--;
	}
	ft_putstr_fd(bot->exec_code, fd);
	close(fd);
	ft_putstr_fd("print_byte_code(): Success\n", log_fd);
	return (OK);
}
