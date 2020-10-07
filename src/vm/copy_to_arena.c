/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_to_arena.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 23:08:29 by aimelda           #+#    #+#             */
/*   Updated: 2020/10/02 10:24:25 by aimelda          ###   ########.fr       */
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
