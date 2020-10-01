/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 17:15:23 by aimelda           #+#    #+#             */
/*   Updated: 2020/09/29 20:29:42 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	introduce_players(t_bot **players)
{
	int	i;

	ft_printf("Introducing contestants...\n");
	i = 0;
	while (players[i])
	{
		ft_printf("* Player %d, weighing %d bytes, ""%s"" (""%s"") !\n", i + 1,
		players[i]->exec_code_size, players[i]->name, players[i]->comment);
		++i;
	}
}

static int	processes_acts(t_vm *vm, t_list *process)
{
	t_process	*cur;

	while (process)
	{
		cur = (t_process*)process->content;
		if (cur->timer == 0)
		{
			cur->instruction = vm->arena[cur->pc] - 1;
			if (cur->instruction >= 0 && cur->instruction < INSTRUCTION_NUM)
				cur->timer = g_op_tab[cur->instruction].cool_down;
		}
		if (cur->timer > 0)
			--(cur->timer);
		if (cur->timer == 0 && execute_instruction(vm, cur) == KO)
			return (KO);
		process = process->next;
	}
	return (OK);
}

static int	dump(char *arena)
{
	int	i;
	int	j;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("0x%0.4x : ", i);
		j = 0;
		while (j++ < DUMP_32)
		{
			ft_printf("%0.2x ", arena[i]);
			++i;
		}
		ft_printf("\n");
	}
	return (OK);
}

static void	check_up(t_vm *vm)
{
	t_list		**addr;
	t_list		*cur;

	vm->num_check += 1;
	addr = &(vm->processes);
	cur = vm->processes;
	while (cur)
		if (((t_process*)cur->content)->alive)
		{
			((t_process*)cur->content)->alive = 0;
			addr = &(cur->next);
			cur = *addr;
		}
		else
		{
			*addr = cur->next;
			ft_lstdelone(cur, free);
			cur = *addr;
		}
	if (vm->num_live >= NBR_LIVE || vm->num_check == MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		vm->num_check = 0;
	}
	vm->num_live = 0;
}

int			fighting(t_vm *vm)
{
	int	countdown;

	introduce_players(vm->players);
	while (vm->processes)
	{
		if (vm->cycles_to_die > 0)
			countdown = vm->cycles_to_die;
		else
			countdown = 1;
		while (countdown)
		{
			if (vm->num_cycle == vm->dump)
				return (dump(vm->arena));
			++(vm->num_cycle);
			if (processes_acts(vm, vm->processes) == KO)
				return (KO);
			--countdown;
		}
		check_up(vm);
	}
	ft_printf("Player %d (%s) won\n",
		vm->survivor + 1, vm->players[vm->survivor]->name);
	return (OK);
}
