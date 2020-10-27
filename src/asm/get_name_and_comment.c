/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_and_comment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slisandr <slisandr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 21:47:18 by slisandr          #+#    #+#             */
/*   Updated: 2020/10/25 01:23:38 by slisandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define NAME 0
#define COMMENT 1

/*
** Called from get_name_and_comment()
**
** This function skips
** - comments
** - empty lines
** - whitespaces in the front part of non-empty line
*/

static char	*skip_to_actual_data(size_t fd)
{
	char	*line;

	while (get_next_line(fd, &line))
	{
		skip_whitespaces(&line);
		if (line[0] != '#' && line[0] != ';' && line[0] != '\0')
			return (line);
	}
	return (NULL);
}

static int	read_data(t_bot *bot, char *line, int *found, size_t fd)
{
	if (!ft_strncmp(line, ".name", 5))
	{
		line += 5;
		skip_whitespaces(&line);
		if (!(get_name_or_comment(
				bot->name,
				PROG_NAME_LENGTH,
				line, fd)))
			return (KO);
		found[NAME] += 1;
		return (OK);
	}
	else if (!ft_strncmp(line, ".comment", 8))
	{
		line += 8;
		skip_whitespaces(&line);
		if (!(get_name_or_comment(
				bot->comment,
				COMMENT_LENGTH,
				line, fd)))
			return (KO);
		found[COMMENT] += 1;
		return (OK);
	}
	return (KO);
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
** This function DOESN'T read the next line after 
** it finds the last quotation mark!
**
** TODO: add more tests!
**
** TODO: fix leaks?
*/

int			get_name_and_comment(t_bot *bot, size_t fd)
{
	int		found[2];
	char	*line;

	if (!bot)
		return (KO);
	found[NAME] = 0;
	found[COMMENT] = 0;
	while (found[NAME] < 1 || found[COMMENT] < 1)
	{
		if (!(line = skip_to_actual_data(fd)) ||
			!read_data(bot, line, found, fd))
			break;
	}
	ft_strdel(&line);
	if (found[NAME] == 1 && found[COMMENT] == 1)
		return (OK);
	return (KO);
}
