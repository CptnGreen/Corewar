/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slisandr <slisandr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 15:59:50 by rfrieda           #+#    #+#             */
/*   Updated: 2020/10/19 00:1 :31y slisandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define NOT_VALID 0
#define VALID 1

/*
** Files to be passed to asm must end with ".s"
*/

static int	check_extension(char *file_name)
{
	int		l;

	l = ft_strlen(file_name);
	if (l < 3 || \
		file_name[l - 1] != 's' || \
		file_name[l - 2] != '.')
		return (BAD_EXT);
	return (OK);
}

/*
** Called from main() on every filename passed to asm as an command line
** argument. Corresponding files are to be opened, read from, processed
** and validated.
*/

int			validate_and_process_file(char *file_name, t_bot *bot)
{
	int		fd;

	ft_memset(bot, '\0', sizeof(t_bot));
	if (check_extension(file_name) == BAD_EXT ||
		(fd = open(file_name, O_RDONLY)) == -1)
	{
		return (NOT_VALID);
	}
	if (!get_name_and_comment(bot, fd) ||
		!get_exec_code(bot, fd))
	{
		close(fd);
		return (NOT_VALID);
	}
	close(fd);
	if (!print_byte_code(file_name, bot))
		return (NOT_VALID);
	return (VALID);
}

int			main(int ac, char **av)
{
	t_bot	bot;
	int		i;

	i = 0;
	while (++i < ac)
	{
		if (validate_and_process_file(av[i], &bot) == NOT_VALID)
			ft_printf("%s cannot be converted to bytecode.\n", av[i]);
		else
			ft_printf("%s was successfully converted to bytecode.\n", av[i]);
	}
	return (EXIT_SUCCESS);
}
