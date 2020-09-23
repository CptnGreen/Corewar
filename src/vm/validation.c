/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 15:21:18 by aimelda           #+#    #+#             */
/*   Updated: 2020/09/23 19:34:11 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	check_extension(char *file_name)
{
	int		len;
	int		extension_len;

	len = ft_strlen(file_name);
	extension_len = ft_strlen(".cor");
	if (len <= extension_len
	|| ft_strcmp(file_name + len - extension_len, ".cor"))
		return (BAD_EXT);
	return (OK);
}

static int	free_players(t_list *players, char *err_description)
{
	ft_lstdel(players, free);
	if (err_description)
		ft_printf(err_description);
	return (KO);
}

void		flag_dump(char *str, t_vm *vm)
{
	int		num; //size_t ???
	char	*num_as_string;

	num = ft_atoi(str);
	num_as_string = ft_itoa(num);
	if (!ft_strcmp(str, num_as_string))
		vm->dump = num;
	free(num_as_string);
}

int 		flag_n(char *str, int *cur_number, int *max_number)
{
	int	num;

	num = ft_atoi(str);
	if(num < 1 && num > MAX_PLAYERS)
		return (KO);
	*cur_number = num - 1;
	if (*cur_number > *max_number)
		*max_number = *cur_number;
	return (OK);
}

static int	arrange_players(t_vm *vm, t_list *unordered_players,
							int num_players, int max_player)
{
	t_list	*tmp;
	int		i;

	if (max_player >= num_players)
		return (free_players(unordered_players, 
		"error: the order number is greater than the total number of players"));
	if (num_players == 0)
		return (free_players(unordered_players, USAGE));
	i = 0;
	while (unordered_players)
	{
		while (vm->players[i] != NULL)
			i++;
		vm->players[i++] = unordered_players->content;
		tmp = unordered_players;
		unordered_players = unordered_players->next;
		free(tmp);
	}
	return (init_arena(vm, num_players));
}

int			validation(t_vm *vm, int argc, char **argv)
{
    t_list	*unordered_players;
    int		col_players;
    int		cur_order_num;
    int		max_order_num;
	int		i;

	unordered_players = NULL;
	col_players = 0;
	cur_order_num = 0;
	max_order_num = 0;
	i = 0;
	while(++i < argc)
		if (check_extension(argv[i]) == OK)
		{
			if (++col_players > MAX_PLAYERS)
				return (free_players(unordered_players)); // "error: too many players."
			if (bot_processing(vm, &unordered_players, cur_order_num, argv[i]) == KO)
				return (free_players(unordered_players, NULL));
			cur_order_num = 0;
		}
		else if (cur_order_num > 0)
			return (free_players(unordered_players)); // "error: invalid sequence of parameters."
		else if (!ft_strcmp(argv[i], "-dump"))
			flag_dump(argv[++i], vm);
		else if (!ft_strcmp(argv[i], "-n"))
		{
			if (flag_n(argv[++i], &cur_order_num, &max_order_num) == KO)
				return (free_players(unordered_players)); // "error: invalid order number of player"
		}
		else
			return (free_players(unordered_players)); // "error: illegal option: argv[i]." --- usage
	return (arrange_players(vm, unordered_players, col_players, max_order_num));
}
