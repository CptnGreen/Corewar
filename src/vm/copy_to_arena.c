/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_to_arena.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 23:08:29 by aimelda           #+#    #+#             */
/*   Updated: 2020/11/27 11:34:56 by fcatina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	copy_to_arena(char *arena, void *src, int pos, int size)
{
	char	*s;

	s = src;
	while (size--)
	{
		pos = get_position(pos);
		arena[pos++] = *s++;
	}
}
