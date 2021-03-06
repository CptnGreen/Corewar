/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_position.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 21:44:17 by aimelda           #+#    #+#             */
/*   Updated: 2020/11/27 11:34:17 by fcatina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

int		get_position(int pos)
{
	if (pos >= MEM_SIZE)
		return (pos % MEM_SIZE);
	if (pos < 0)
		return (get_position(MEM_SIZE + pos));
	return (pos);
}
