# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slisandr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/21 15:25:21 by slisandr          #+#    #+#              #
#    Updated: 2020/11/28 12:21:23 by slisandr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re libftprintf norm asm vm unit-test memcheck test

CC = gcc
CFLAGS = -Wall -Werror -Wextra
INC	=	-I "includes/" \
		-I "ft_printf/includes/" \
		-I "ft_printf/libft/includes/"

# --------------- COMMON ------------------------------------

all: libftprintf asm vm

libftprintf:
	@ make -C ft_printf/

re: fclean all

OBJ_DIR = obj

# --------------- ASSEMBLER: PREREQUISITES ------------------

EXEC_ASM = asm

SRC_DIR_ASM = src/asm
SRC_RAW_ASM = \
		main.c \
		op.c \
		print_byte_code.c \
		get_name_or_comment.c \
		get_name_and_comment.c \
		get_exec_code.c \
		get_instruction.c \
		new_label.c \
		tobytes.c \
		skip_whitespaces.c \
		get_number.c

SRC_ASM = $(addprefix $(SRC_DIR_ASM)/,$(SRC_RAW_ASM))

OBJ_DIR_ASM = $(OBJ_DIR)/asm
OBJ_ASM = $(addprefix $(OBJ_DIR_ASM)/,$(SRC_RAW_ASM:.c=.o))

# --------------- ASSEMBLER: COMPILATION --------------------

asm: libftprintf $(OBJ_DIR_ASM) $(OBJ_ASM)
	$(CC) $(CFLAGS) -o $(EXEC_ASM) $(OBJ_ASM) $(INC) -L "ft_printf/" -lftprintf
$(OBJ_DIR_ASM)/%.o: $(SRC_DIR_ASM)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)
$(OBJ_DIR_ASM):
	mkdir -p $(OBJ_DIR_ASM)

# ---------------------- VM: PREREQUISITES ------------------

EXEC_VM = corewar

SRC_DIR_VM = src/vm
SRC_RAW_VM = \
		main.c \
		add.c \
		aff.c \
		op.c \
		and_or_xor.c \
		bot_processing.c \
		copy_from_arena.c \
		copy_to_arena.c \
		execute_instruction.c \
		fighting.c \
		fork.c \
		get_position.c \
		init_arena.c \
		instructions.c \
		ld.c \
		ldi_lldi.c \
		lfork.c \
		live.c \
		lld.c \
		st.c \
		sti.c \
		sub.c \
		validation.c \
		zjmp.c

SRC_VM = $(addprefix $(SRC_DIR_VM)/,$(SRC_RAW_VM))

OBJ_DIR_VM = $(OBJ_DIR)/vm
OBJ_VM = $(addprefix $(OBJ_DIR_VM)/,$(SRC_RAW_VM:.c=.o))

# ---------------------- VM: COMPILATION --------------------

vm: libftprintf $(OBJ_DIR_VM) $(OBJ_VM)
	$(CC) $(CFLAGS) -o $(EXEC_VM) $(OBJ_VM) $(INC) -L "ft_printf/" -lftprintf
$(OBJ_DIR_VM)/%.o: $(SRC_DIR_VM)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)
$(OBJ_DIR_VM):
	mkdir -p $(OBJ_DIR_VM)

# --------------- CLEANUP -----------------------------------

clean:
	@ rm -rf $(OBJ_DIR) bots/*.cor
	@ make -C ft_printf/ clean
	@ make -C ft_printf/libft/ clean
fclean: clean
	@ rm -f $(EXEC_ASM) $(EXEC_VM)
	@ make -C ft_printf/ fclean
	@ make -C ft_printf/libft/ fclean

# --------------- TESTS -------------------------------------

norm:
	@ ./scripts/check_norm.sh
unit-test: all
	@ printf "\nUnit tests (ceedling)\n=============\n\n"
	@ ceedling
memcheck: all
	@ printf "\nFunctional testing and memory leaks' check\n=============\n"
	@ ./scripts/check_leaks.sh -av

test: unit-test memcheck norm