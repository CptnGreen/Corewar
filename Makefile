# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slisandr <slisandr@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/21 15:25:21 by slisandr          #+#    #+#              #
#    Updated: 2020/10/20 23:28:46 by slisandr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re libftprintf norm asm unit-test func-test

CC = gcc
CFLAGS = -Wall -Werror -Wextra
INC	=	-I "includes/" \
		-I "ft_printf/includes/" \
		-I "ft_printf/libft/includes/"

# --------------- COMMON ------------------------------------

all: libftprintf asm vm

libftprintf:
	@ make -C ft_printf/

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
		get_number.c

SRC_ASM = $(addprefix $(SRC_DIR_ASM)/,$(SRC_RAW_ASM))

OBJ_DIR_ASM = obj/asm
OBJ_ASM = $(addprefix $(OBJ_DIR_ASM)/,$(SRC_RAW_ASM:.c=.o))

# --------------- ASSEMBLER: COMPILATION --------------------

asm: libftprintf $(OBJ_DIR_ASM) $(OBJ_ASM)
	$(CC) $(CFLAGS) -o $(EXEC_ASM) $(OBJ_ASM) $(INC) -L "ft_printf/" -lftprintf
$(OBJ_DIR_ASM)/%.o: $(SRC_DIR_ASM)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)
$(OBJ_DIR_ASM):
	mkdir -p $(OBJ_DIR_ASM)

# ---------------------- VM: PREREQUISITES ------------------

EXEC_VM = vm

SRC_DIR_VM = src/vm
SRC_RAW_VM = \
		main.c \
		add.c \
		aff.c \
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

OBJ_DIR_VM = obj/vm
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
	@ rm -rf $(OBJ_DIR_ASM) $(OBJ_DIR_VM)
	@ make -C ft_printf/ clean
	@ make -C ft_printf/libft/ clean
fclean: clean
	@ rm -f $(EXEC_ASM) $(EXEC_VM)
	@ make -C ft_printf/ fclean
	@ make -C ft_printf/libft/ fclean

# --------------- OTHER -------------------------------------

re: fclean all

norm: fclean
	@ norminette includes/* src/*
unit-test: all
	@ ceedling
func-test: all
	./$(EXEC_ASM) resources/vm_champs/champs/championships/2014/bguy/sam_2.0.s
	./$(EXEC_VM) resources/vm_champs/champs/championships/2014/bguy/sam_2.0.cor
memcheck: asm
	@ valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(EXEC_ASM)
	@ vim valgrind-out.txt
