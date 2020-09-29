/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_number.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 16:18:48 by aimelda           #+#    #+#             */
/*   Updated: 2020/09/28 16:52:50 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static char	det_sign(char **line)
{
	if (**line == '-')
	{
		++(*line);
		return (-1);
	}
	return (1);
}

int			get_number(char **line)
{
	long long	res;
	char		sign;

	res = 0;
	sign = det_sign(line);
	while (ft_isdigit(**line))
	{
		if (sign && (res > INT64_MAX / 10
		|| (res == INT64_MAX / 10 && **line > INT64_MAX % 10)))
		{
			if (sign == 1)
				res = -1;
			else
				res = 0;
			sign = 0;
		}
		else if (sign)
			res = res * 10 + **line - '0';
		++(*line);
	}
	if (sign == -1)
		return (-res);
	return (res);
}
