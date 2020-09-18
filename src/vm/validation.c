#include "corewar.h"

static int	check_extension(char *file_name)
{
	int		len;
	int		extension_len;

	len = ft_strlen(file_name);
	extension_len = ft_strlen(".cor");
	if (len <= extension_len
	|| ft_strcmp(file_name + len - extension_len, ".cor"))
		return (BAD_EXT);
	return (OK);
}

static int	free_players(t_list *players)
{
	ft_lstdel(players, free);
	return (KO);
}

void	flag_dump(char *str, t_vm *vm)
{
	int		num; //size_t ???
	char	*num_as_string;

	num = ft_atoi(str);
	num_as_string = ft_itoa(num);
	if (!ft_strcmp(str, num_as_string))
		vm->dump = num;
	free(num_as_string);
}

int flag_n(char *str)
{
	int num;

	num = ft_atoi(str);
	if(num < 0 && num > MAX_PLAYERS)
		error("flag -n"); // error
	return num - 1;
}

int	valid(t_vm *vm, int argc, char *argv[])
{
    t_list *players_without_n;
	t_list *temp_list;//?
    int col_players;
    int cur_serial_number;
    int max_serial_number;
	int i;

	col_players = 0;
	cur_serial_number = 0;
	max_serial_number = 0;
	i = 0;
	players_without_n = NULL;
	while(i < argc)
		if (check_extension(argv[i]) == OK)
		{
			if (++col_players > MAX_PLAYERS)
				return (free_players(players_without_n)); // "error: too many players, max = MAX_PLAYERS."
			if (!cur_serial_number)
			{
				if (!(temp_list = ft_lstnew(NULL)))
					return (free_players(players_without_n)); // "error: cannot allocate memory."
				ft_lstadd(&players_without_n, temp_list);
				if (proccessing_bot(&(players_without_n->content)) == KO) // check function
					return (free_players(players_without_n)); // without message
			}
			else if(vm->players[cur_serial_number] == NULL)
			{
				if (proccessing_bot(&(vm->players[cur_serial_number])) == KO) // check function
					return (free_players(players_without_n)); // without message
			}
			else
				return (free_players(players_without_n)); // "error: two or more players are assigned the same number."
			cur_serial_number = 0;
		}
		else if (cur_serial_number > 0)
			return (free_players(players_without_n)); // "error: invalid sequence of parameters."
		else if (!ft_strcmp(argv[i], "-dump"))
			flag_dump(argv[++i], vm);
		else if (!ft_strcmp(argv[i], "-n"))
		{
			cur_serial_number = flag_n(argv[++i]);
			if (cur_serial_number > max_serial_number)
				max_serial_number = cur_serial_number;
		}
		else
			return (free_players(players_without_n)); // "error: illegal option: argv[i]."
	if (max_serial_number > col_players)
		return (free_players(players_without_n)); // "error: the order number is greater than the total number of players."
	i = 0;
	while (players_without_n)
	{
		while (vm->players[i] != NULL)
			i++;
		vm->players[i++] = players_without_n->content;
		temp_list = players_without_n;
		players_without_n = players_without_n->next;
		free(temp_list);
	}
}
