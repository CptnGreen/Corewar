/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slisandr <slisandr@student.21-s~.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 15:21:18 by aimelda           #+#    #+#             */
/*   Updated: 2020/11/01 21:56:19 by slisandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define FLAG_DUMP "-dump"
#define FLAG_N "-n"

static t_list	*g_unordered_players;
static int		g_num_players;
static int		g_cur_order_num;
static int		g_max_order_num;

static int	check_extension(char *file_name)
{
	int		len;
	int		extension_len;

	len = ft_strlen(file_name);
	extension_len = ft_strlen(".cor");
	if (len <= extension_len ||
		ft_strcmp(file_name + len - extension_len, ".cor"))
		return (BAD_EXT);
	return (OK);
}

static int	error(char *err_description)
{
	ft_lstdel(&g_unordered_players, free);
	if (err_description)
		ft_printf("%s\n", err_description);
	return (KO);
}

static int	handle_flag(t_vm *vm, char *flag, char *param)
{
	int		num;
	char	*num_as_string;

	num = ft_atoi(param);
	num_as_string = ft_itoa(num);
	if (!ft_strcmp(flag, FLAG_N))
	{
		if (ft_strcmp(param, num_as_string) || num < 1 || num > MAX_PLAYERS)
		{
			free(num_as_string);
			return (error("error: invalid player number."));
		}
		g_cur_order_num = num;
		if (g_cur_order_num > g_max_order_num)
			g_max_order_num = g_cur_order_num;
	}
	else
	{
		if (!ft_strcmp(param, num_as_string))
			vm->dump = num;
	}
	free(num_as_string);
	return (OK);
}

static int	arrange_players(t_vm *vm)
{
	t_list	*tmp;
	int		i;

	if (g_num_players == 0)
		return (error(USAGE));
	if (g_max_order_num > g_num_players)
		return (error("error: incorrect order number."));
	i = g_num_players - 1;
	while (g_unordered_players)
	{
		while (vm->players[i] != NULL)
			--i;
		vm->players[i--] = g_unordered_players->content;
		tmp = g_unordered_players;
		g_unordered_players = g_unordered_players->next;
		free(tmp);
	}
	return (init_arena(vm, g_num_players));
}

int			validation(t_vm *vm, int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
		if (check_extension(argv[i]) == OK)
		{
			if (++g_num_players > MAX_PLAYERS)
				return (error("error: too many players."));
			if (bot_processing(vm, &g_unordered_players,
							g_cur_order_num, argv[i]) == KO)
				return (error(NULL));
			g_cur_order_num = 0;
		}
		else if (g_cur_order_num > 0)
			return (error("error: invalid sequence of parameters."));
		else if (!ft_strcmp(argv[i], FLAG_N) || !ft_strcmp(argv[i], FLAG_DUMP))
		{
			if (++i == argc)
				return (error(USAGE));
			if (handle_flag(vm, argv[i - 1], argv[i]) == KO)
				return (KO);
		}
		else
			return (error(USAGE));
	return (arrange_players(vm));
}
