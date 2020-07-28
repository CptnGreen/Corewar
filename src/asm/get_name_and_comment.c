#include "corewar.h"

/*
** This one is called from main()
**
** Purpose of this function is to fill BOTH name and comment
** fields in bot structure, or shoot error if:
** - there is no name or no comment
** - there is more than just one name or comment
** - there is nothing after name and comment lines
** - get_next_line() returns (-1)
**
** This function DOESN'T read the next line after it
** finds the last quotation mark!
**
**  TODO: add more tests?
*/

int		get_name_and_comment(t_bot *bot, char *line, size_t fd)
{
	int	found_name;
	int	found_comment;

	found_name = 0;
	found_comment = 0;
	while (!found_name || !found_comment)
	{
		if (ft_strstr(line, ".name"))
		{
			found_name += 1;
			get_name_or_comment(bot->name, PROG_NAME_LENGTH, line, fd);
		}
		else if (ft_strstr(line, ".comment"))
		{
			found_comment += 1;
			get_name_or_comment(bot->comment, COMMENT_LENGTH, line, fd);
		}
		else
			return (KO);
		if (found_name > 1 || found_comment > 1 || get_next_line(fd, &line) != 1)
			return (KO);
	}
	return (OK);
}
