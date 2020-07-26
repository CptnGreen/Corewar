#include "corewar.h"

/*
** Explicit is better than implicit
*/

t_bot	*init_bot(void)
{
    t_bot	*bot;

    bot = (t_bot *)ft_memalloc(sizeof(t_bot));
    return(bot);
}
