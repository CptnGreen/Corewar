/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_name_and_comment.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slisandr <slisandr@student.21-sc...>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 21:47:18 by slisandr          #+#    #+#             */
/*   Updated: 2020/07/25 20:31:12 by slisandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Simpler version of ft_strtrim() which trims only the front
** part of the line but not the back one.
*/

char	*skip_whitespaces(char *line)
{
	int		i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i += 1;
	return (line + i);
}

/*
** This function skips
** - comments
** - empty lines
** - whitespaces in the front part of non-empty line
*/

char	*skip_to_actual_data(size_t fd)
{
	char	*line;

	while (get_next_line(fd, &line))
	{
		line = skip_whitespaces(line);
		if (line[0] != '#' && line[0] != ';' && line[0] != '\0')
			return (line);
	}
	return (NULL);
}

/*
** This one is called from main()
**
** Purpose of this function is to fill BOTH name and comment
** fields in bot structure, or shoot error if:
** - there is no name or no comment
** - there is more than just one name or comment
** - there is anything but whitespaces before ".name" or ".comment"
** - there is anything but whitespaces between ".name"/".comment" and quotations
** - there is anything but whitespaces after last quotation mark
** - get_next_line() returns (-1)
** - bot is NULL
**
** This function DOESN'T read the next line after it
** finds the last quotation mark!
**
** TODO: add more tests!
**
** TODO: fix leaks?
*/

int		get_name_and_comment(t_bot *bot, size_t fd)
{
	int		found_name;
	int		found_comment;
	char	*line;

	if (!bot)
		return (KO);
	found_name = 0;
	found_comment = 0;
	while (!found_name || !found_comment)
	{
		if (!(line = skip_to_actual_data(fd)))
			break ;
		if (!ft_strncmp(line, ".name", 5) && get_name_or_comment(\
				bot->name, PROG_NAME_LENGTH, skip_whitespaces(line + 5), fd))
			found_name += 1;
		else if (!ft_strncmp(line, ".comment", 8) && get_name_or_comment(\
				bot->comment, COMMENT_LENGTH, skip_whitespaces(line + 8), fd))
			found_comment += 1;
		if (found_name > 1 || found_comment > 1)
			break ;
	}
	ft_strdel(&line);
	return ((found_name == 1 && found_comment == 1) ? OK : KO);
}
