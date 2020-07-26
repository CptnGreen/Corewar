#include "corewar.h"

/*
** This function is called from get_name_and_comment().
** It is included as a separate module in order to be easily
** tested.
**
** It is supposed to receive line containg ".name" or ".comment"
** substring.
**
** Purpose of this function is to fill bot->name or bot->comment
** depending on the contents of the received line.
**
** TODO: add more elaborate tests!
**
** TODO: fix leaks
*/

char	*get_name_or_comment(char *field, char *line, size_t fd)
{
	char	*ptr;

	line = ft_strchr(line, '"') + 1;
	while (1)
	{
		if ((ptr = ft_strrchr(line, '"')))
		{
			line = ft_strtrim(line);
			line[ft_strlen(line) - 1] = '\0';
			ft_strcat(field, ft_strtrim(line));
			break ;
		}
		ft_strcat(field, ft_strtrim(line));
		field[ft_strlen(field)] = '\n';
		get_next_line(fd, &line);
	}
	return (0);
}
