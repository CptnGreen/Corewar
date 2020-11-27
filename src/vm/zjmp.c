/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 22:59:00 by aimelda           #+#    #+#             */
/*   Updated: 2020/11/27 11:34:35 by fcatina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** SUBJECT:
** there’s never been, isn’t and will never be an argument’s coding byte behind
** this operation where the opcode is 9. It will take an index and jump to this
** address if the carry is 1.
*/

int		zjmp(t_vm *vm, t_process *process)
{
	short	ind;

	if (process->carry == 1)
	{
		copy_from_arena(vm->arena, &ind, process->pc + 1, IND_SIZE);
		process->pc = get_position(process->pc + ind % IDX_MOD);
	}
	return (OK);
}
