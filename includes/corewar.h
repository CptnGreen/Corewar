#ifndef COREWAR_H
# define COREWAR_H

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

# define T_REG_OR_T_DIR 3
# define T_REG_OR_T_IND 5
# define T_DIR_OR_T_IND 6
# define T_REG_OR_T_DIR_OR_T_IND 7

typedef struct		s_bot{
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	size_t			exec_code_size;
	char			exec_code[CHAMP_MAX_SIZE + 1];
}					t_bot;

t_bot	*init_bot(void);

char	*chars_to_bytes(char const *str);
char	*get_byte_code(char const *asm_code);

int		print_byte_code(char *file_name, t_bot *bot);
int		check_extension(char *file_name);
int		create_and_open_file_cor(int i, char *name, char *file_name);
void	put_in_cor_magic_header_and_botName(int fd, t_bot *bot);
int		put_exec_codeSize_in_cor(t_bot *bot, int fd);


char	*get_magic_header(void);

char	*get_name_or_comment(char *field, char *line, size_t fd);
int		get_name_and_comment(t_bot *bot, char *line, size_t fd);

int		*get_exec_code(t_bot *bot, size_t fd);

#endif
