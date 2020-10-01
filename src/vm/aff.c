/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 22:06:38 by aimelda           #+#    #+#             */
/*   Updated: 2020/10/01 22:06:40 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		aff(t_vm *vm, t_process *process)
{
	char	reg_number;
	int		*arg_value;

	reg_number = vm->arena[process->pc + 2] - 1;
	arg_value = process->registries[reg_number];
	ft_printf("Aff: %c\n", (char)*arg_value);
	return (OK);
}
