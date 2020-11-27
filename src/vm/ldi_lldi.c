/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi_lldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 15:14:04 by aimelda           #+#    #+#             */
/*   Updated: 2020/11/27 11:34:38 by fcatina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** SUBJECT:
**
** ldi:
** ldi, ldi, as per the name, does not imply to go swimming in chestnut cream,
** even if its code is 0x0a. Instead, it will use 2 indexes and 1 registry,
** adding the first two, treating that like an address, reading a value of a
** registry’s size and putting it on the third.
**
** lldi:
** Opcode 0x0e. Same as ldi, but does not apply any modulo to the addresses.
** It will however, modify the carry.
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
	args[0] = get_arg(vm, process, &pc, type >> 6);
	args[1] = get_arg(vm, process, &pc, type >> 4);
	reg = vm->arena[get_position(pc)] - 1;
	return (reg);
}

int			ldi(t_vm *vm, t_process *process)
{
	int				args[2];
	int				result;
	unsigned char	reg;

	reg = get_args(vm, process, args);
	copy_from_arena(vm->arena, &result,
	process->pc + (args[0] + args[1]) % IDX_MOD, REG_SIZE);
	ft_memcpy(process->registries[reg], &result, REG_SIZE);
	return (OK);
}

int			lldi(t_vm *vm, t_process *process)
{
	int				args[2];
	int				result;
	unsigned char	reg;

	reg = get_args(vm, process, args);
	copy_from_arena(vm->arena, &result,
	process->pc + args[0] + args[1], REG_SIZE);
	ft_memcpy(process->registries[reg], &result, REG_SIZE);
	process->carry = result ? 0 : 1;
	return (OK);
}
