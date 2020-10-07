/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_from_arena.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 23:53:27 by aimelda           #+#    #+#             */
/*   Updated: 2020/10/02 10:24:47 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	copy_from_arena(char *arena, void *dst, int pos, int size)
{
	char	*s;

	s = dst;
	while (size--)
	{
		pos = get_position(pos);
		*s++ = arena[pos++];
	}
}
