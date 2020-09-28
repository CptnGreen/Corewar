/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_instruction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 16:31:04 by aimelda           #+#    #+#             */
/*   Updated: 2020/09/28 19:41:25 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	get_position(int pos)
{
	if (pos >= MEM_SIZE)
		return (pos % MEM_SIZE);
	return (pos);
}

static char	get_arg_type(char code)
{
	const char	mask = 3;

	code &= mask;
	if (code == REG_CODE)
		return (T_REG);
	else if (code == DIR_CODE)
		return (T_DIR);
	else if (code == IND_CODE)
		return (T_IND);
	return (0);
}

static void	move_process(t_process *process, char *arena)
{
	int		dir_size;

	if (g_op_tab[process->instruction - 1]->is_dir_like_ind)
		dir_size = IND_SIZE;
	else
		dir_size = DIR_SIZE;
	if (g_op_tab[process->instruction - 1]->have_arg_type_code)
	{
		
	}
	else
		process->pc += 1 + dir_size;
}

static int	code_is_correct(t_op *instruction, char code)
{
	int		n;
	int		i;
	char	cur_type;

	n = instruction->arg_number;
	code >>= (MAX_ARGS_NUMBER - n) * 2;
	i = 0;
	while (i < n)
	{
		cur_type = get_arg_type(code);
		if (instruction->arg_types[i] & cur_type != cur_type)
			return (0);
		++i;
		code >>= 2;
	}
	return (1);
}

int			execute_instruction(t_vm *vm, t_process *process)
{
	const char	type_code = vm->arena[get_position(process->pc + 1)];
	const char	dir_size = g_op_tab[process->instruction - 1]->is_dir_like_ind ? IND_SIZE : DIR_SIZE;

	if (process->instruction <= 0 || process->instruction > INSTRUCTION_NUM)
		process->pc += 1;
	else
	{
		// type_code = vm->arena[get_position(process->pc + 1)];
		if (g_op_tab[process->instruction - 1]->have_arg_type_code)
		{
			if (code_is_correct(g_op_tab[process->instruction - 1], type_code)
			&& valid_reg())
			{
				//if execute successfully;
			}
		}
		else
			;//exec
		//move
	}
	process->pc = get_position(process->pc);
	return (OK);
}
