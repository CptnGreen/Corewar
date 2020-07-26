#ifndef COREWAR_H
# define COREWAR_H

# include "libftprintf.h"
# include "op.h"

/*
** Assembly part
*/

typedef struct	s_bot
{
    unsigned char	bot_name[PROG_NAME_LENGTH + 1];
	unsigned char	comment[COMMENT_LENGTH + 1];
    unsigned int	exec_size;
    unsigned char	exec_code[CHAMP_MAX_SIZE + 1];
}				t_bot;


char	*get_magic_header(void);
char	*chars_to_bytes(char const *str);
char	*get_zeroes(unsigned int n_zeroes);
char	*get_byte_code(char const *asm_code);
int   print_byte_code(char *file_name, t_bot *bot);

#endif
