#include "corewar.h"

char	*skip_whitespaces(char *line)
{
	int		i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i += 1;
	return (line + i);
}

/*
** This one is called from main()
**
** Purpose of this function is to fill BOTH name and comment
** fields in bot structure, or shoot error if:
** - there is no name or no comment
** - there is more than just one name or comment
** - there is nothing after name and comment lines
** - there is anything but whitespaces before ".name" or ".comment"
** - there is anything but whitespaces between ".name"/".comment" and quotations
** - there is anything but whitespaces after last quotation mark
** - get_next_line() returns (-1)
** - line or bot is NULL
**
** This function DOESN'T read the next line after it
** finds the last quotation mark!
**
** TODO: add more tests!
**
** TODO: fix leaks?
*/

int		get_name_and_comment(t_bot *bot, char *line, size_t fd)
{
	int	found_name;
	int	found_comment;

	if (!line || !bot)
		return (KO);
	found_name = 0;
	found_comment = 0;
	while (!found_name || !found_comment)
	{
		line = skip_whitespaces(line);
		if (!ft_strncmp(line, ".name", 5) && get_name_or_comment(\
				bot->name, PROG_NAME_LENGTH, skip_whitespaces(line + 5), fd))
			found_name += 1;
		else if (!ft_strncmp(line, ".comment", 8) && get_name_or_comment(\
				bot->comment, COMMENT_LENGTH, skip_whitespaces(line + 8), fd))
			found_comment += 1;
		else
			return (KO);
		if (found_name > 1 || found_comment > 1 || \
			get_next_line(fd, &line) != 1)
			return (KO);
	}
	return (OK);
}
