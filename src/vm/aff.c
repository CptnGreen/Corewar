/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 22:06:38 by aimelda           #+#    #+#             */
/*   Updated: 2020/11/27 11:35:00 by fcatina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** SUBJECT:
** The opcode is 10 in the hexadecimal. There is an argument’s coding byte,
** even if it’s a bit silly because there is only 1 argument that is a registry,
** which is a registry, and its content is interpreted by the character’s ASCII
** value to display on the standard output. The code is modulo 256.
*/

int		aff(t_vm *vm, t_process *process)
{
	unsigned char	reg_number;
	int				*arg_value;

	reg_number = vm->arena[get_position(process->pc + 2)] - 1;
	arg_value = (int*)process->registries[reg_number];
	ft_printf("Aff: %c\n", (char)*arg_value);
	return (OK);
}
