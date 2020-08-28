/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 23:06:08 by aimelda           #+#    #+#             */
/*   Updated: 2020/08/28 22:42:44 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include "libftprintf.h"

# include <stdint.h> // delete before push to vogsphere

/*
** Useful defines:
*/

# define OK 1
# define KO 0

/*
** Error codes:
*/

# define BAD_EXT -2

/*
** Assembly part
*/

# define INSTRUCTION_MAX_SIZE 14
# define MAGIC_HEADER "\x00\xea\x83\xf3"
# define DIV_ZEROES "\x00\x00\x00\x00"

typedef struct	s_bot
{
	char	name[PROG_NAME_LENGTH + 1];
	char	comment[COMMENT_LENGTH + 1];
	int		exec_code_size;
	char	exec_code[CHAMP_MAX_SIZE + INSTRUCTION_MAX_SIZE];
}				t_bot;

typedef struct	s_label
{
	char	*name;
	int		addr;
	t_list	*queue;
}				t_label;

typedef struct	s_deferred
{
	int		dest_addr;
	int		instr_addr;
	char	size;
}				t_deferred;

char			*get_byte_code(char const *asm_code);

int				print_byte_code(char *file_name, t_bot *bot);

int				get_name_or_comment(char *field, size_t max_len, char *line,
					size_t fd);
int				get_name_and_comment(t_bot *bot, size_t fd);

int				get_number(char **line);
void			tobytes(char *dest, int nbr, char size);
int				get_exec_code(t_bot *bot, size_t fd);
int				get_instruction(t_bot *bot, char *line, t_list **labels,
					t_op *ins);
t_label			*new_label(t_list **label, char *line, size_t len, int addr);
void			skip_whitespaces(char **line);

/*
** VM part
**
** struct s_process:
** pc			- is a register that stores the address of the next instruction;
** timer		- countdown cycles before executing an instruction (see op_tab);
** registries	- registries to store data;
** instruction	- the order number of current instruction;
** carry		- flag, if the latest operation was successful;
** alive		- flag, if the process reported 'alive' since last checkup;
**
** struct s_vm:
** processes	 - the list of alive processes;
** players		 - array with all players' information;
** num_cycle	 - the number of current cycle;
** dump			 - the num of cycles after which the program must be terminated;
** cycles_to_die - countdown cycles before checkup;
** num_live		 - the number of executed 'live' instruction since last checkup;
** num_check	 - the number of checkups since last decrement cycles_to_die;
** survivor		 - the player whose process was the last to execute 'live';
** arena		 - arena, according to the subject;
*/

typedef struct	s_process
{
	int		pc;
	int		timer;
	char	registries[REG_NUMBER][REG_SIZE];
	char	instruction;
	char	carry;
	char	alive;
}				t_process;

typedef struct	s_vm
{
	t_list	*processes;
	t_bot	*players[MAX_PLAYERS];
	size_t	num_cycle;
	size_t	dump;
	int		cycles_to_die;
	int		num_live;
	int		num_check;
	int		survivor;
	char	arena[MEM_SIZE];
}				t_vm;

int				init_arena(t_vm *vm, int num_players);

#endif
