/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 22:06:46 by aimelda           #+#    #+#             */
/*   Updated: 2020/11/27 11:34:40 by fcatina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** SUBJECT:
** there is no argument’s coding byte, take an index, opcode 0x0c. Create a
** new process that will inherit the different states of its father, except
** its PC, which will be put at (PC + (1st parameter % IDX_MOD)).
*/

int		fork__(t_vm *vm, t_process *process)
{
	t_process	*new_process;
	t_list		*new_node;
	short		arg;

	if ((new_node = ft_lstnew(NULL)))
	{
		ft_lstadd(&(vm->processes), new_node);
		if ((new_node->content = malloc(sizeof(t_process))))
		{
			new_process = new_node->content;
			ft_memcpy(new_process, process, sizeof(t_process));
			copy_from_arena(vm->arena, &arg, process->pc + 1, IND_SIZE);
			new_process->pc = get_position(process->pc + arg % IDX_MOD);
			return (OK);
		}
	}
	perror("error");
	return (KO);
}
