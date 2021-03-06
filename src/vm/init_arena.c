/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 17:53:12 by aimelda           #+#    #+#             */
/*   Updated: 2020/11/27 11:34:44 by fcatina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	add_process(t_list **players, int address, int num_player)
{
	t_list		*player;

	if (!(player = ft_lstnew(NULL)))
		return (KO);
	ft_lstadd(players, player);
	if (!(player->content = ft_memalloc(sizeof(t_process))))
		return (KO);
	((t_process*)player->content)->pc = address;
	**(((t_process*)player->content)->registries) = num_player;
	return (OK);
}

/*
** The function:
** - distributes the execution codes of the players in the arena;
** - initializes the list of original processes;
** - saves the order numbers of the players in the first register of processes;
** - sets initial value of cycles_to_die equal to CYCLE_TO_DIE;
** - sets initial value of survivor equal to the latest player's number;
*/

int			init_arena(t_vm *vm, int num_players)
{
	int		i;
	int		delta;
	int		offset;

	i = 0;
	delta = MEM_SIZE / num_players;
	offset = 0;
	while (i < num_players)
	{
		ft_memcpy(vm->arena + offset, vm->players[i]->exec_code,
			vm->players[i]->exec_code_size);
		if ((add_process(&vm->processes, offset, ++i)) == KO)
			return (KO);
		offset += delta;
	}
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->survivor = num_players - 1;
	return (OK);
}
