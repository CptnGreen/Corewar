#include "corewar.h"

/*
** Called from main()
*/

static int	create_and_open_file_cor(char *file_name)
{
	char	*name;
	int		len;
	int		fd;

	len = ft_strlen(file_name) + 2;
	if (!(name = (char*)malloc(len + 1)))
		return (-1);
	ft_strncpy(name, file_name, len - 3);
	ft_strcpy(name + len - 3, "cor");
	fd = open(name, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	free(name);
	return (fd);
}

static void	put_bytes(char *src, int size, int fd)
{
	int		i;

	i = 0;
	while (i < size)
		ft_putchar_fd(src[i++], fd);
}

static void	put_exec_code_size_in_cor(t_bot *bot, int fd)
{
	int		i;
	char	*res;

	i = 3;
	res = (char*)(&bot->exec_code_size);
	while (i >= 0)
	{
		ft_putchar_fd(res[i], fd);
		i--;
	}
}

int			print_byte_code(char *file_name, t_bot *bot)
{
	int		fd;

	if ((fd = create_and_open_file_cor(file_name)) == -1)
		return (KO);
	put_bytes(MAGIC_HEADER, 4, fd);
	put_bytes(bot->name, PROG_NAME_LENGTH, fd);
	put_bytes(DIV_ZEROES, 4, fd);
	put_exec_code_size_in_cor(bot, fd);
	put_bytes(bot->comment, COMMENT_LENGTH, fd);
	put_bytes(DIV_ZEROES, 4, fd);
	put_bytes(bot->exec_code, bot->exec_code_size, fd);
	close(fd);
	return (OK);
}
