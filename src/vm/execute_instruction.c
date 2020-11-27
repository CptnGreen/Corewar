/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_instruction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 16:31:04 by aimelda           #+#    #+#             */
/*   Updated: 2020/11/27 11:34:14 by fcatina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	get_dir_size(const t_op *instruction)
{
	if (instruction->is_dir_like_ind)
		return (IND_SIZE);
	return (DIR_SIZE);
}

static char	get_arg_type(const t_op *instruction, int *size, char code)
{
	const char	mask = 3;

	code &= mask;
	if (code == IND_CODE)
	{
		*size += IND_SIZE;
		return (T_IND);
	}
	else if (code == DIR_CODE)
	{
		*size += get_dir_size(instruction);
		return (T_DIR);
	}
	return (T_REG);
}

static int	code_is_correct(const t_op *instruction, char *arena,
			int *instruction_size, int pc)
{
	int		ret_val;
	int		i;
	char	code;
	char	cur_type;

	ret_val = 1;
	code = arena[get_position(pc + 1)];
	i = instruction->arg_number;
	code >>= (MAX_ARGS_NUMBER - i) * 2;
	while (i--)
	{
		cur_type = get_arg_type(instruction, instruction_size, code);
		if (ret_val && (instruction->arg_types[i] & cur_type) != cur_type)
			ret_val = 0;
		if (cur_type == T_REG)
		{
			if (ret_val && (arena[get_position(pc + *instruction_size)] < 1
			|| arena[get_position(pc + *instruction_size)] > REG_NUMBER))
				ret_val = 0;
			++(*instruction_size);
		}
		code >>= 2;
	}
	return (ret_val);
}

int			execute_instruction(t_vm *vm, t_process *process)
{
	int		instruction_size;

	if (process->instruction >= INSTRUCTION_NUM)
		process->pc += 1;
	else
	{
		instruction_size = 1;
		if (g_op_tab[process->instruction].have_arg_type_code)
		{
			++instruction_size;
			if (code_is_correct(&g_op_tab[process->instruction], vm->arena,
			&instruction_size, process->pc)
			&& g_instructions[process->instruction](vm, process) == KO)
				return (KO);
		}
		else
		{
			instruction_size += get_dir_size(&g_op_tab[process->instruction]);
			if (g_instructions[process->instruction](vm, process) == KO)
				return (KO);
		}
		process->pc += instruction_size;
	}
	process->pc = get_position(process->pc);
	return (OK);
}
