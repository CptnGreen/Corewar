#include "corewar.h"

/*
** TODO: write concise comment here
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
			if (get_next_line(fd, &line) == 0)
				break ;
		}
		else if (ft_strstr(line, ".comment"))
		{
			found_comment += 1;
			get_name_or_comment(bot->comment, COMMENT_LENGTH, line, fd);
			if (get_next_line(fd, &line) == 0)
				break ;
		}
	}
	if (found_name != 1 || found_comment != 1)
		return (KO);
	return (OK);
}
