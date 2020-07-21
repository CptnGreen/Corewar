#ifndef COREWAR_H
# define COREWAR_H

# include "libftprintf.h"
# include "op.h"

# define MAGIC

/*
** Assembly part
*/

typedef struct  s_bot
{
    unsigned int	magic;
    char            prog_name[PROG_NAME_LENGTH + 1];
    unsigned int	prog_size;
    char            comment[COMMENT_LENGTH + 1];
}               t_bot;


char	*get_magic_header(void);
char	*chars_to_bytes(char const *str);
char	*get_zeroes(unsigned int n_zeroes);
char	*get_byte_code(char const *asm_code);

#endif
