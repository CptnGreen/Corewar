#ifndef COREWAR_H
# define COREWAR_H

# include "libftprintf.h"

/*
** Assembly part
*/

char	*get_byte_code(char const *asm_code);
char	*get_magic_header(void);
char	*get_name(char const *name);
char	*get_zeroes(unsigned int n_zeroes);
char	*get_comment(char const *comment);

#endif
