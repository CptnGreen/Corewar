#include "corewar.h"

int	main(int ac, char **av)
{
	t_bot *bot;
	int i;
	int fd;

	i = 0;
	if (!(bot = init_bot()))
		return(KO);
	while (++i != ac)
	{

		if (!(check_extension(av[i])))
			continue;
		fd = open(av[i],O_RDONLY);
		if (fd < 0)
			return(KO);
		if ((!(get_name_and_comment(bot,fd))))
			return(KO);
		if (!(get_exec_code()))
			return(KO);
		close(fd);
		if(!(print_byte_code(fd,bot)))
			return(KO);
	}
	free(bot);
	return (0);
}
