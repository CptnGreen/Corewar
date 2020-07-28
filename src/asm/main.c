#include "corewar.h"

int	main(int ac, char **av)
{	
	t_bot *bot;
	int i;
	int err;
	int fd;
	
	i = 0;
	err = 1;
	if (!(bot = init_bot()))
		return(KO);
	while (++i != ac)
	{
		err = check_extension(av[i]);
		if (err < 0)
			continue;
		fd = open(av[i],O_RDONLY);
		if (fd < 0)
			return(KO);
		if ((!(err = get_name_and_comment(bot,fd))))
			return(KO);
		if (!(err = get_exec_code()))
			return(KO);
		close(fd);
		if(!(err = print_byte_code(fd,bot)))
			return(KO);
	}
	free(bot);	
	return (0);
}