/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 22:06:58 by aimelda           #+#    #+#             */
/*   Updated: 2020/10/02 16:03:15 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** SUBJECT:
** Take a random argument and a registry. Load the value of the first argument
** in the registry. Its opcode is 10 in binary and it will change the carry.
*/

int		ld(t_vm *vm, t_process *process)
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
		copy_from_arena(vm->arena, &dir, process->pc + ind % IDX_MOD, DIR_SIZE);
	}
	else
		copy_from_arena(vm->arena, &dir, process->pc + 2, DIR_SIZE);
	ft_memcpy(process->registries[reg_number], &dir, REG_SIZE);
	process->carry = dir ? 0 : 1; // condition acc.to Brazhnik
	return (OK);
}
