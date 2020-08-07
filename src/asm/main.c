/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrieda <rfrieda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 15:59:50 by rfrieda           #+#    #+#             */
/*   Updated: 2020/08/03 16:02:03 by rfrieda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define SUCCESS 0
#define FAILURE 1

#define LOG "log_asm.txt"

int			main(int ac, char **av)
{
	t_bot	*bot;
	int		i;
	int		fd;
	int		log_fd;

	i = 0;
	if (!(bot = init_bot()) || \
		(log_fd = open(LOG, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR)) < 0)
		return (FAILURE);
	while (++i < ac)
	{
		if ((fd = open(av[i], O_RDONLY)) < 0 || \
			!get_name_and_comment(bot, fd, log_fd) || \
			!get_exec_code(bot, fd, log_fd))
		{
			ft_putstr_fd("main(): Something is wrong\n", log_fd);
			continue ;
		}
		close(fd);
		if (!print_byte_code(av[i], bot))
			continue ;
	}
	destroy_bot(bot);
	close(log_fd);
	return (SUCCESS);
}
