#ifndef COREWAR_H
# define COREWAR_H

# include "libftprintf.h"

char	*get_byte_code(char const *asm_code);
char	*get_magic_header(void);
char	*get_name(char const *name);

#endif
