#include "corewar.h"

/*
** This function is called from get_name_and_comment().
** It is included as a separate module in order to be easily
** tested.
**
** It is supposed to receive line starting with quotation mark.
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
	size_t		l;

	if (!line || line[0] != '"')
		return (KO);
	line += 1;
	while (1)
	{
		l = ft_strlen(line);
		if (line[l - 1] == '"')
		{
			line[l - 1] = '\0';
			if (ft_strlen(field) + (l - 1) > max_len)
				return (KO);
			ft_strcat(field, line);
			break ;
		}
		if (ft_strlen(field) + (l + 1) > max_len)
			return (KO);
		ft_strcat(field, line);
		field[ft_strlen(field)] = '\n';
		get_next_line(fd, &line);
	}
	return (OK);
}
