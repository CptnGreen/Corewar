# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/21 15:25:21 by slisandr          #+#    #+#              #
#    Updated: 2020/07/21 20:05:22 by aimelda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re libftprintf norm asm test

CC = clang
CFLAGS = -Wall -Werror -Wextra

# --------------- ASSEMBLER: PREREQUISITES ------------------

EXEC_ASM = asm.out

SRC_DIR_ASM = src/asm
SRC_RAW_ASM = \
		main.c \
		init_bot.c \
		get_byte_code.c \
		print_byte_code.c \
		check_extension.c \
		create_and_open_file_cor.c \
		put_in_cor_magic_header_and_bot_name.c \
		put_exec_code_size_in_cor.c \
		get_magic_header.c \
		get_name_or_comment.c \
		get_name_and_comment.c \
		get_exec_code.c \
		get_instruction.c \
		new_label.c \
		tobytes.c \
		skip_whitespaces.c \
		get_number.c \
		op.c

SRC_ASM = $(addprefix $(SRC_DIR_ASM)/,$(SRC_RAW_ASM))

OBJ_DIR = obj
OBJ_ASM = $(addprefix $(OBJ_DIR)/,$(SRC_RAW_ASM:.c=.o))

# --------------- ASSEMBLER: COMPILATION --------------------

all: asm

asm: libftprintf $(OBJ_DIR) $(OBJ_ASM)
	$(CC) $(CFLAGS) -o $(EXEC_ASM) $(OBJ_ASM) \
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
	@ norminette includes/corewar.h src/asm
test: all
	@ ceedling
memcheck: asm
	@ valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(EXEC_ASM)
	@ vim valgrind-out.txt
