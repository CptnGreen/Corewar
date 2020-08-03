/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrieda <rfrieda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 15:59:50 by rfrieda           #+#    #+#             */
/*   Updated: 2020/08/03 15:59:58 by rfrieda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


int	main(int ac, char **av)
{
	t_bot *bot;
	int i;
	int fd;

	i = 0;
	if (!(bot = init_bot()))
		return(KO);
	while (++i != ac)
	{
		if (!(check_extension(av[i])))
			continue;
		fd = open(av[i], O_RDONLY);
		if (fd < 0)
			continue;
		if ((!(get_name_and_comment(bot,fd))))
			continue;
		if (!(get_exec_code()))
			continue;
		close(fd);
		if(!(print_byte_code(fd,bot)))
			continue;
	}
	free(bot);
	return (0);
}
