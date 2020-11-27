/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 22:40:02 by aimelda           #+#    #+#             */
/*   Updated: 2020/11/27 11:34:21 by fcatina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** SUBJECT:
** take a registry and a registry or an indirect and store the value of the
** registry toward a second argument. Its opcode is 0x03. For example,
** st r1, 42 store the value of r1 at the address (PC + (42 % IDX_MOD))
*/

int		st(t_vm *vm, t_process *process)
{
	char			type;
	unsigned char	reg_number;
	short			ind;
	unsigned char	reg2;

	type = vm->arena[get_position(process->pc + 1)];
	reg_number = vm->arena[get_position(process->pc + 2)] - 1;
	if (type >> 4 & T_IND)
	{
		copy_from_arena(vm->arena, &ind, process->pc + 3, IND_SIZE);
		copy_to_arena(vm->arena, process->registries[reg_number],
		process->pc + ind % IDX_MOD, REG_SIZE);
	}
	else
	{
		reg2 = vm->arena[get_position(process->pc + 3)] - 1;
		ft_memcpy(process->registries[reg2],
		process->registries[reg_number], REG_SIZE);
	}
	return (OK);
}
