/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 22:07:24 by aimelda           #+#    #+#             */
/*   Updated: 2020/10/02 18:09:25 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** SUBJECT:
** The instruction that allows a process to stay alive. It can also record that
** the player whose number is the argument is indeed alive. No argument’s coding
** byte, opcode 0x01. Oh and its only argument is on 4 bytes.
*/

int		live(t_vm *vm, t_process *process)
{
	int		*arg_value;

	process->alive = 1;
	vm->num_live += 1;
	arg_value = (int*)process->registries[0];
	if (*arg_value > 0 && *arg_value <= MAX_PLAYERS
	&& vm->players[*arg_value - 1]) // condition acc.to Subject
		vm->survivor = *arg_value - 1;
	return (OK);
}
