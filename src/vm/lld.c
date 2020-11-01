/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slisandr <slisandr@student.21-s~.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 22:10:26 by aimelda           #+#    #+#             */
/*   Updated: 2020/11/01 21:57:27 by slisandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** SUBJECT:
** Means long-load, so it’s opcode is obviously 13. It the same as ld, but
** without % IDX_MOD. Modify the carry.
*/

int		lld(t_vm *vm, t_process *process)
{
	int				dir;
	short			ind;
	char			type;
	unsigned char	reg_number;

	type = vm->arena[get_position(process->pc + 1)];
	reg_number = vm->arena[get_position(process->pc + 2 + DIR_SIZE)] - 1;
	if (type >> 6 & T_IND)
	{
		copy_from_arena(vm->arena, &ind, process->pc + 2, IND_SIZE);
		copy_from_arena(vm->arena, &dir, process->pc + ind, DIR_SIZE);
	}
	else
		copy_from_arena(vm->arena, &dir, process->pc + 2, DIR_SIZE);
	ft_memcpy(process->registries[reg_number], &dir, REG_SIZE);
	process->carry = dir ? 0 : 1;
	return (OK);
}
