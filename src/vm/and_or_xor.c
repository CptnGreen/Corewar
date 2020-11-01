/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_xor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slisandr <slisandr@student.21-s~.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 11:47:47 by aimelda           #+#    #+#             */
/*   Updated: 2020/11/01 21:52:46 by slisandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** SUBJECT:
**
** AND:
** Apply an & (bit-to-bit AND) over the first two arguments and store the result
** in a registry, which is the third argument. Opcode 0x06. Modifies the carry.
**
** OR:
** This operation is an bit-to-bit OR, in the same spirit and principle of and,
** its opcode is obviously 7.
**
** XOR:
** Acts like and with an exclusive OR. As you will have guessed, its opcode in
** octal is 10.
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

int			and(t_vm *vm, t_process *process)
{
	int				args[2];
	int				result;
	unsigned char	reg;

	reg = get_args(vm, process, args);
	result = args[0] & args[1];
	ft_memcpy(process->registries[reg], &result, REG_SIZE);
	process->carry = result ? 0 : 1;
	return (OK);
}

int			or(t_vm *vm, t_process *process)
{
	int				args[2];
	int				result;
	unsigned char	reg;

	reg = get_args(vm, process, args);
	result = args[0] | args[1];
	ft_memcpy(process->registries[reg], &result, REG_SIZE);
	process->carry = result ? 0 : 1;
	return (OK);
}

int			xor(t_vm *vm, t_process *process)
{
	int				args[2];
	int				result;
	unsigned char	reg;

	reg = get_args(vm, process, args);
	result = args[0] ^ args[1];
	ft_memcpy(process->registries[reg], &result, REG_SIZE);
	process->carry = result ? 0 : 1;
	return (OK);
}
