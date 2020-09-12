#include "corewar.h"

void error(char *str,t_list *list)
{
    write(1,"Error ",7);
    write(1,str,ft_strlen(str));
    write(1,"\n",1);
}
