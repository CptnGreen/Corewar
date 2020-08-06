#ifndef COREWAR_H
# define COREWAR_H

# include <stdint.h> // remove later!

# include "op.h"
# include "libftprintf.h"

/*
** Useful defines:
*/

# define OK 1
# define KO 0

/*
** Assembly part
*/

# define INSTRUCTION_MAX_SIZE 14

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

t_bot	*init_bot(void);

char	*get_byte_code(char const *asm_code);

int		print_byte_code(char *file_name, t_bot *bot);
int		check_extension(char *file_name);
int		create_and_open_file_cor(int i, char *file_name);
void	put_in_cor_magic_header_and_bot_name(int fd, t_bot *bot);
int		put_exec_code_size_in_cor(t_bot *bot, int fd);

char	*get_magic_header(void);

int		get_name_or_comment(char *field, size_t max_len, char *line, size_t fd);
int		get_name_and_comment(t_bot *bot, size_t fd);

int		get_number(char **line);
void	tobytes(char *dest, int nbr, char size);
int		get_exec_code(t_bot *bot, size_t fd);
int		get_instruction(t_bot *bot, char *line, t_list **labels, t_op *ins);
t_label	*new_label(t_list **label, char *line, size_t len, int addr);
void	skip_whitespaces(char **line);

#endif
