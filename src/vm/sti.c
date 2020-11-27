/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 15:50:38 by aimelda           #+#    #+#             */
/*   Updated: 2020/11/27 11:34:25 by fcatina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** SUBJECT:
** Opcode 11. Take a registry, and two indexes (potentially registries) add the
** two indexes, and use this result as an address where the value of the first
** parameter will be copied.
*/

static int	get_arg(t_vm *vm, t_process *process, int *pc, char type)
{
	int				dir;
	short			ind;
	unsigned char	reg;

	if (type & T_REG)
	{
		reg = vm->arena[get_position(*pc)] - 1;
		*pc += 1;
		return (*(int*)process->registries[reg]);
	}
	else if (type & T_DIR)
	{
		copy_from_arena(vm->arena, &dir, *pc, DIR_SIZE);
		*pc += DIR_SIZE;
		return (dir);
	}
	else
	{
		copy_from_arena(vm->arena, &ind, *pc, IND_SIZE);
		copy_from_arena(vm->arena, &dir, process->pc + ind % IDX_MOD, DIR_SIZE);
		*pc += IND_SIZE;
		return (dir);
	}
}

static char	get_args(t_vm *vm, t_process *process, int *args)
{
	char	type;
	char	reg;
	int		pc;

	pc = process->pc + 1;
	type = vm->arena[get_position(pc++)] - 1;
	reg = vm->arena[get_position(pc++)] - 1;
	args[0] = get_arg(vm, process, &pc, type >> 4);
	args[1] = get_arg(vm, process, &pc, type >> 2);
	return (reg);
}

int			sti(t_vm *vm, t_process *process)
{
	int				args[2];
	unsigned char	reg;

	reg = get_args(vm, process, args);
	copy_to_arena(vm->arena, process->registries[reg],
	process->pc + (args[0] + args[1]) % IDX_MOD, REG_SIZE);
	return (OK);
}
