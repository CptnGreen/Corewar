/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_from_arena.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 23:53:27 by aimelda           #+#    #+#             */
/*   Updated: 2020/11/27 11:34:53 by fcatina          ###   ########.fr       */
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
