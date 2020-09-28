# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/21 15:25:21 by slisandr          #+#    #+#              #
#    Updated: 2020/09/28 13:50:04 by aimelda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re libftprintf norm asm test

CC = clang
CFLAGS = -Wall -Werror -Wextra
INC	=	-I "includes/" \
		-I "ft_printf/includes/" \
		-I "ft_printf/libft/includes/"

# --------------- ASSEMBLER: PREREQUISITES ------------------

EXEC_ASM = asm

SRC_DIR_ASM = src/asm
SRC_RAW_ASM = \
		main.c \
		print_byte_code.c \
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
	$(CC) $(CFLAGS) -o $(EXEC_ASM) $(OBJ_ASM) $(INC) -L "ft_printf/" -lftprintf
$(OBJ_DIR)/%.o: $(SRC_DIR_ASM)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)
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
	@ make -C ft_printf/ fclean
	@ make -C ft_printf/libft/ fclean

# --------------- OTHER -------------------------------------

re: fclean all

norm: fclean
	@ norminette includes/* src/*
test: all
	@ ceedling
test_asm: all
	@ ./$(EXEC_ASM) resources/vm_champs/champs/championships/2014/bguy/sam_2.0.s
memcheck: asm
	@ valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(EXEC_ASM)
	@ vim valgrind-out.txt
