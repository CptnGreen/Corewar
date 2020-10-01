/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 22:40:02 by aimelda           #+#    #+#             */
/*   Updated: 2020/10/01 22:40:03 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		st(t_vm *vm, t_process *process)
{
	char	type;
	char	reg_number;
	void	*arg_value;

	type = vm->arena[process->pc + 1];
	reg_number = vm->arena[process->pc + 2] - 1;
	arg_value = vm->arena + process->pc + 2;
	if (type >> 4 & T_IND)
		arg_value = vm->arena + process->pc + *(short*)arg_value % IDX_MOD;
	else
		arg_value = process->registries[*(char*)arg_value];
	ft_memcpy(arg_value, process->registries[reg_number], REG_SIZE);
	return (OK);
}