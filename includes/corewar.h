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

typedef struct		s_bot{
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	size_t			exec_code_size;
	char			exec_code[CHAMP_MAX_SIZE + 1];
}					t_bot;

t_bot	*init_bot(void);
int		destroy_bot(t_bot *bot);

char	*chars_to_bytes(char const *str);
char	*get_byte_code(char const *asm_code);

char	*get_magic_header(void);

int		get_name_or_comment(char *field, size_t max_len, char *line, size_t fd);
int		get_name_and_comment(t_bot *bot, size_t fd);

#endif
