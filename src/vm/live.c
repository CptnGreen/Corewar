/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 22:07:24 by aimelda           #+#    #+#             */
/*   Updated: 2020/10/01 22:10:04 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		live(t_vm *vm, t_process *process)
{
	int		*arg_value;

	process->alive = 1;
	arg_value = process->registries[0];
	if (*arg_value > 0 && *arg_value <= MAX_PLAYERS
	&& vm->players[*arg_value - 1]) // acc.to Subject
		vm->survivor = *arg_value - 1;
	return (OK);
}
