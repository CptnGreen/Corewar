/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instruction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 22:17:43 by aimelda           #+#    #+#             */
/*   Updated: 2020/08/06 10:50:18 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern char		g_codes_of_arg_type[4][4];

static long		get_dir_or_ind(char **line, t_bot *bot, t_op *ins, char type)
{
	char	size;

	if (**line == ':')
	{
		++(*line);
		return (type | T_LAB | ins->is_dir_like_ind);
	}
	else if (ft_isdigit(**line) || **line == '-')
	{
		if (type == T_DIR && !(ins->is_dir_like_ind))
			size = DIR_SIZE;
		else
			size = IND_SIZE;
		tobytes(bot->exec_code + bot->exec_code_size, get_number(line), size);
		bot->exec_code_size += size;
		return (type - (type == T_IND));
	}
	return (KO);
}

static int		get_arg_type(t_bot *bot, char **line, t_op *ins, char permitted)
{
	if (**line == 'r')
	{
		++(*line);
		if ((permitted & T_REG)
		&& (bot->exec_code[bot->exec_code_size] = (char)get_number(line)) > 0
		&& bot->exec_code[bot->exec_code_size++] <= REG_NUMBER)
			return (REG_CODE);
	}
	else if (**line == '%')
	{
		++(*line);
		if (permitted & T_DIR)
			return (get_dir_or_ind(line, bot, ins, T_DIR));
	}
	else
	{
		if (permitted & T_IND)
			return (get_dir_or_ind(line, bot, ins, T_IND));
	}
	return (KO);
}

static t_label	*check_label(char **line, t_bot *bot, t_list **labels)
{
	char	*label;

	label = *line;
	while (**line && ft_strchr(LABEL_CHARS, **line))
		++(*line);
	if (*line == label)
		return (NULL);
	return (new_label(labels, label, *line - label, INT32_MAX));
}

static int		get_value(t_label *label, t_bot *bot, char *arg_type, int addr)
{
	t_list	*value;
	char	size;

	if (!label)
		return (KO);
	if (*arg_type == (T_LAB | T_DIR))
		size = DIR_SIZE;
	else
		size = IND_SIZE;
	if (label->addr != INT32_MAX)
		tobytes(bot->exec_code + bot->exec_code_size, label->addr - addr, size);
	else
	{
		if (!(value = ft_lstnew(NULL))
		|| !(value->content = malloc(sizeof(t_deferred))))
			return (KO);
		ft_lstadd(&(label->queue), value);
		((t_deferred*)value->content)->dest_addr = bot->exec_code_size;
		((t_deferred*)value->content)->instr_addr = addr;
		((t_deferred*)value->content)->size = size;
	}
	bot->exec_code_size += size;
	if (*arg_type & T_DIR)
		return ((*arg_type = DIR_CODE));
	return ((*arg_type = IND_CODE));
}

int				get_instruction(t_bot *bot, char *line, t_list **labels
					, t_op *ins)
{
	int		instr_addr;
	char	i;
	char	argtype;

	instr_addr = bot->exec_code_size;
	bot->exec_code[bot->exec_code_size++] = ins->order;
	if (ins->have_arg_type_code)
		bot->exec_code[bot->exec_code_size++] = 0;
	i = 0;
	while (i < ins->arg_number)
	{
		skip_whitespaces(&line);
		if (!(argtype = get_arg_type(bot, &line, ins, ins->arg_types[i++]))
		|| ((argtype & T_LAB) &&
		!get_value(check_label(&line, bot, labels), bot, &argtype, instr_addr)))
			return (KO);
		if (ins->have_arg_type_code)
			bot->exec_code[instr_addr + 1] |= g_codes_of_arg_type[argtype][i];
		skip_whitespaces(&line);
		if (*line == SEPARATOR_CHAR && i < ins->arg_number)
			++line;
		else if (*line != '\0')
			return (KO);
	}
	return (bot->exec_code_size <= CHAMP_MAX_SIZE);
}
