/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bytes_from_number.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:12:32 by aimelda           #+#    #+#             */
/*   Updated: 2020/08/06 07:11:19 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	tobytes(char *dest, int nbr, char size)
{
	short	short_nbr;
	char	*nbr_bytes;

	if (size == DIR_SIZE)
	{
		nbr_bytes = (char*)&nbr;
	}
	else
	{
		short_nbr = (short)nbr;
		nbr_bytes = (char*)&short_nbr;
	}
	while (size--)
		*dest++ = nbr_bytes[size];
}
