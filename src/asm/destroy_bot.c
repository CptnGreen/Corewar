#include "corewar.h"

/*
** Little helper hunction just to
** - save a couple of lines in several places
** - bring some clarity to the code
*/

int	destroy_bot(t_bot *bot)
{
	if (bot)
	{
		free(bot);
		bot = NULL;
		return (OK);
	}
	return (KO);
}
