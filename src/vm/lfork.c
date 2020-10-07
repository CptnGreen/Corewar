/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 22:07:15 by aimelda           #+#    #+#             */
/*   Updated: 2020/10/02 17:30:12 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** SUBJECT:
** means long-fork, to be able to fork abut straw from a distance of 15 meters,
** exactly like with its opcode. Same as a fork without modulo in the address.
*/

int		lfork(t_vm *vm, t_process *process)
{
	t_process	*new_process;
	t_list		*new_node;
	short		arg;

	// ft_printf("----");//del
	if ((new_node = ft_lstnew(NULL)))
	{
		ft_lstadd(&(vm->processes), new_node);
		if ((new_node->content = malloc(sizeof(t_process))))
		{
			new_process = new_node->content;
			ft_memcpy(new_process, process, sizeof(t_process));
			copy_from_arena(vm->arena, &arg, process->pc + 1, IND_SIZE);
			new_process->pc = get_position(process->pc + arg);
			return (OK);
		}
	}
	perror("error");
	return (KO);
}
