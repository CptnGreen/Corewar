/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tobytes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slisandr <slisandr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:12:32 by aimelda           #+#    #+#             */
/*   Updated: 2020/10/21 21:56:42 by slisandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Called from get_instruction() and get_exec_code()
**
** size can be only 1 or 4?
*/

void	tobytes(char *dest, int nbr, char size)
{
	short	short_nbr;
	char	*nbr_bytes;

	if (size == DIR_SIZE)
		nbr_bytes = (char*)&nbr;
	else
	{
		short_nbr = (short)nbr;
		nbr_bytes = (char*)&short_nbr;
	}
	while (size--)
		*dest++ = nbr_bytes[(int)size];
}
