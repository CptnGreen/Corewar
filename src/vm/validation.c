#include "corewar.h"

static int	check_extension(char *file_name)
{
	int		l;

	l = ft_strlen(file_name);
	if (l < 5 || \
		file_name[l - 1] != 'r' || \
		file_name[l - 2] != 'o' || \
		file_name[l - 3] != 'c' || \
		file_name[l - 4] != '.' )
		return (BAD_EXT);
	return (OK);
}
void	flag_dump(char *str,t_vm *vm)
{
	int		num; //size_t ???
	char	*num_as_string;

// следующую строку привести в тип int
	num = ft_atoi(str);
	num_as_string = ft_itoa(num);
	// полученное значение укладывается в тип int / size_t?
	if (!ft_strcmp(str, num_as_string))
	// присвоить значение в переменную dump структуры t_vm*
		vm->dump = num;
}

int flag_n(char *str)
{
	int num;

	num = ft_atoi(str);
	if(num < 0 && num > MAX_PLAYERS)
		error("flag -n");
	return num - 1;
}
int valid(t_vm *vm, int argc, char *argv[])
{
	// инициализи
	// ровать переменную (список) для хранения ботов,
	//  чьи порядковые номера не определены флагом "-n"
    t_list *players_without_n;
	t_list *temp_list;

    int col_players;

    int serial_number;
    int max_serial_number;
	int i;

	col_players = 0;
	serial_number = 0;
	max_serial_number = 0;
	i = 0;
	players_without_n = NULL;
	// ft_bzero(players_without_n,sizeof(t_list));

	while(i < argc)
	{
		if (check_extension(argv[i]) == OK)
		{
			col_players++;
			if (col_players > MAX_PLAYERS)
				{
					error("wrong col_players");
					ft_lstdel(players_without_n,free);
				}

			 // значение переменной порядкового номера больше нуля?
				else if (!serial_number)
				{
					// создать и добавить новый элемент в начало списка для хранения ботов;
					// успешно?
					if (!(temp_list = ft_lstnew(NULL)))
						error("the element didn't add");
					ft_lstadd(&players_without_n, temp_list);

					// передать в функцию ниже адрес содержимого созданного элемента списка
					if (proccessing_bot(&(players_without_n->content)) == KO)
						error("errrs");
				}
					// элемент массива players* структуры t_vm* с порядковым
					// номером равным значению переменной порядкового
					// номера равен NULL?(  есть повторение номера?)
				else if(!vm->players[serial_number] == NULL)
				{
					error("null");
					ft_lstdel(players_without_n,free);
					// сообщить об ошибке
					// очистить список и содержимое.
					// вернуть код ошибки
					if (proccessing_bot(&(vm->players[serial_number])) == KO)
						error("errr");
						ft_lstdel(players_without_n,free);
				}
				else
					error("err");
					// обнулить переменную порядкового номера
				serial_number = 0;
		}
		else
		{
			if (serial_number > 0)
			{
				error(error);
				ft_lstdel(players_without_n,free);
			}
			// сообщить об ошибке
			// очистить список и содержимое
			// вернуть код ошибки
			if (!ft_strcmp(argv[i], "-dump"))
				flag_dump(argv[++i], vm);
			else if (!ft_strcmp(argv[i], "-n"))
			{
				// присвоить полученное значение в переменную порядкового номера
				serial_number = flag_n(argv[++i]);
				if(serial_number > max_serial_number)
				// ное значение порядкового номера больше чем значение максимального порядкового номера?
					max_serial_number = serial_number;
				// сообщить об ошибке
				// очистить список и содержимое
				// вернуть код ошибки
			}
		}
	}
	if(max_serial_number > col_players)
		{
			error("err");
			ft_lstdel(players_without_n,free);
		}
	i = 0;
	// для каждого элемента списка ботов (с начала)
	while(players_without_n)
	{
		while (vm->players[i] != NULL)
			i++;
		vm->players[i++] = players_without_n->content;
		// free(node);
		players_without_n = players_without_n->next;
	}
}

int main()
{
	return(0);
}
