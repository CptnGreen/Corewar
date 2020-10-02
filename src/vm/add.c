/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 11:15:33 by aimelda           #+#    #+#             */
/*   Updated: 2020/10/02 16:08:04 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** SUBJECT:
** Opcode 4. Take three registries, add the first two, and place the result
** in the third, right before modifying the carry.
*/

static int	addition(void *addend1, void *addend2)
{
	return (*(int*)addend1 + *(int*)addend2);
}

int			add(t_vm *vm, t_process *process)
{
	unsigned char	reg1;
	unsigned char	reg2;
	unsigned char	reg3;
	int				sum;

	reg1 = vm->arena[get_position(process->pc + 2)] - 1;
	reg2 = vm->arena[get_position(process->pc + 3)] - 1;
	reg3 = vm->arena[get_position(process->pc + 4)] - 1;
	sum = addition(process->registries[reg1], process->registries[reg2]);
	ft_memcpy(process->registries[reg3], &sum, REG_SIZE);
	process->carry = sum ? 0 : 1; // condition acc.to Brazhnik
	return (OK);
}
