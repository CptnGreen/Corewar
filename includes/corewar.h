#ifndef COREWAR_H
# define COREWAR_H

# include "libftprintf.h"

/*
** Assembly part
*/

char	*get_magic_header(void);
char	*chars_to_bytes(char const *str);
char	*get_zeroes(unsigned int n_zeroes);
char	*get_byte_code(char const *asm_code);

#endif
