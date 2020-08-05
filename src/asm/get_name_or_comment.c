/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_name_or_comment.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slisandr <slisandr@student.21-sc...>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 21:47:18 by slisandr          #+#    #+#             */
/*   Updated: 2020/07/25 20:31:12 by slisandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char	*find_closing_quotation_mark(char *line)
{
	int		i;

	if (line[0] == '"')
		return (line + 0);
	i = 1;
	while (line[i])
	{
		if (line[i] == '"' && line[i - 1] != '\\')
			return (line + i);
		i += 1;
	}
	return (NULL);
}

int		trim_rest_of_line(char *line)
{
	int		i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i += 1;
	if (!line[i] || line[i] == '#' || line[i] == ';')
		return (OK);
	return (KO);
}

/*
** This function is called from get_name_and_comment().
** It is included as a separate module in order to be easily
** tested.
**
** It is supposed to receive a line starting with quotation mark.
**
** Purpose of this function is to fill bot->name or bot->comment
** depending on the contents of the received line.
**
** TODO: add more tests!
**
** TODO: fix leaks?
*/

int		get_name_or_comment(char *field, size_t max_len, char *line, size_t fd)
{
	char	*pos;

	if (!line || line[0] != '"')
		return (KO);
	line += 1;
	while (1)
	{
		if ((pos = find_closing_quotation_mark(line)))
		{
			if (!trim_rest_of_line(pos + 1))
				return (KO);
			*pos = '\0';
			if (ft_strlen(field) + ft_strlen(line) > max_len)
				return (KO);
			ft_strcat(field, line);
			break ;
		}
		if (ft_strlen(field) + (ft_strlen(line) + 1) > max_len)
			return (KO);
		ft_strcat(field, line);
		field[ft_strlen(field)] = '\n';
		get_next_line(fd, &line);
	}
	return (OK);
}
