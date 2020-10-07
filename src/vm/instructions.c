/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 19:47:00 by aimelda           #+#    #+#             */
/*   Updated: 2020/10/02 16:18:31 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	(*g_instructions[INSTRUCTION_NUM])(t_vm *, t_process *) =
{
	live,
	ld,
	st,
	add,
	sub,
	and,
	or,
	xor,
	zjmp,
	ldi,
	sti,
	fork__,
	lld,
	lldi,
	lfork,
	aff
};
