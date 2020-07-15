# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slisandr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/21 15:25:21 by slisandr          #+#    #+#              #
#    Updated: 2020/02/26 12:34:10 by slisandr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re libftprintf norm asm

CC = clang
CFLAGS = -Wall -Werror -Wextra

# --------------- ASSEMBLER: PREREQUISITES ------------------

EXEC_ASM = asm

SRC_DIR_ASM = src/asm
SRC_RAW_ASM = \
	  get_byte_code.c \
	  get_magic_header.c
SRC_ASM = $(addprefix $(SRC_DIR_ASM)/,$(SRC_RAW_ASM))

OBJ_DIR = obj
OBJ_ASM = $(addprefix $(OBJ_DIR)/,$(SRC_RAW_ASM:.c=.o))

MAIN_RAW_ASM = main.c
MAIN_ASM = $(addprefix $(SRC_DIR_ASM)/,$(MAIN_RAW_ASM))

# --------------- ASSEMBLER: COMPILATION --------------------

all: asm

asm: libftprintf $(OBJ_DIR) $(OBJ_ASM)
	$(CC) $(CFLAGS) -o $(EXEC_ASM) $(OBJ_ASM) $(MAIN_ASM) \
		-I "includes/" \
		-I "ft_printf/includes/" \
		-I "ft_printf/libft/includes/" \
		-L "ft_printf/" -lftprintf \
		-L "ft_printf/libft/" -lft
$(OBJ_DIR)/%.o: $(SRC_DIR_ASM)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ \
		-I "includes/" \
		-I "ft_printf/includes/" \
		-I "ft_printf/libft/includes/" 
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
libftprintf:
	@ make -C ft_printf/

# --------------- CLEANUP -----------------------------------

clean:
	@ rm -rf $(OBJ_DIR)
	@ make -C ft_printf/ clean
	@ make -C ft_printf/libft/ clean
fclean: clean
	@ rm -f $(EXEC_ASM)
	@ make -C ft_printf/libft/ fclean

# --------------- OTHER -------------------------------------

re: fclean all

norm: fclean
	@ make -C ft_printf/ norm
	@ make -C ft_printf/libft/ norm
	@ norminette includes/ src/
