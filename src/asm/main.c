/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 15:59:50 by rfrieda           #+#    #+#             */
/*   Updated: 2020/09/28 16:53:44 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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

int			main(int ac, char **av)
{
	t_bot	*bot;
	int		i;
	int		fd;

	i = 0;
<<<<<<< HEAD
	if (!(bot = (t_bot *)ft_memalloc(sizeof(t_bot))))
		return (FAILURE);
=======
	if (!(bot = (t_bot *)malloc(sizeof(t_bot))))
		return (EXIT_FAILURE);
>>>>>>> 00cb53e4f8f6b75f18a73f5bb14369d573328e4c
	while (++i < ac)
	{
		ft_memset(bot, '\0', sizeof(t_bot));
		if (check_extension(av[i]) == BAD_EXT
		|| (fd = open(av[i], O_RDONLY)) == -1)
		{//del
			ft_putstr_fd("ERROR: Invalid extension or file can't opened\n", STDERR_FILENO);//del
			continue ;
		}//del
		if (!get_name_and_comment(bot, fd)
		|| !get_exec_code(bot, fd))
		{
			ft_putstr_fd("ERROR: Error in get_name_and_comment() or in get_exec_code()\n", STDERR_FILENO);//del
			close(fd);
			continue ;
		}
		close(fd);
		if (!print_byte_code(av[i], bot))
		{//del
			ft_putstr_fd("ERROR: Error in printing byte code\n", STDERR_FILENO);//del
			continue ;
		}//del
	}
	free(bot);
	return (EXIT_SUCCESS);
}
