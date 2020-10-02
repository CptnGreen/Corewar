/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 11:39:11 by aimelda           #+#    #+#             */
/*   Updated: 2020/10/02 16:07:46 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** SUBJECT:
** Same as add, but with the opcode est 0b101, and uses a substraction.
*/

static int	subtraction(void *minuend, void *subtrahend)
{
	return (*(int*)minuend - *(int*)subtrahend);
}

int			sub(t_vm *vm, t_process *process)
{
	unsigned char	reg1;
	unsigned char	reg2;
	unsigned char	reg3;
	int				diff;

	reg1 = vm->arena[get_position(process->pc + 2)] - 1;
	reg2 = vm->arena[get_position(process->pc + 3)] - 1;
	reg3 = vm->arena[get_position(process->pc + 4)] - 1;
	diff = subtraction(process->registries[reg1], process->registries[reg2]);
	ft_memcpy(process->registries[reg3], &diff, REG_SIZE);
	process->carry = diff ? 0 : 1; // condition acc.to Brazhnik
	return (OK);
}
