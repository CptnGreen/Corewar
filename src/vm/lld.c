/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 22:10:26 by aimelda           #+#    #+#             */
/*   Updated: 2020/10/01 22:31:30 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		lld(t_vm *vm, t_process *process)
{
	char	type;
	char	reg_number;
	int		*arg_value;

	type = vm->arena[process->pc + 1];
	reg_number = vm->arena[process->pc + 2 + DIR_SIZE] - 1;
	arg_value = vm->arena + process->pc + 2;
	if (type >> 6 & T_IND)
		arg_value = vm->arena + process->pc + *(short*)arg_value;	
	ft_memcpy(process->registries[reg_number], arg_value, REG_SIZE);
	process->carry = *arg_value ? 0 : 1; // acc.to Brazhnik
	return (OK);
}