/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 22:06:46 by aimelda           #+#    #+#             */
/*   Updated: 2020/10/01 22:06:49 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		fork__(t_vm *vm, t_process *process)
{
	t_process	*new_process;
	short		*arg;

	if ((new_process = (t_process*)malloc(sizeof(t_process))))
	{
		memcpy(new_process, process, sizeof(t_process));
		arg = vm->arena + process->pc + 1;
		process->pc += *arg % IDX_MOD;
		return (OK);
	}
	perror("error");
	return (KO);
}
