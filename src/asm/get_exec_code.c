/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 13:49:32 by aimelda           #+#    #+#             */
/*   Updated: 2020/08/28 21:47:50 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern t_op		*g_op_tab[17];
extern int		g_next_op_tab_elem;

static void	del_label(void *node)
{
	if (node)
	{
		free(((t_label*)node)->name);
		ft_lstdel(&(((t_label*)node)->queue), free);
		free(node);
	}
}

static int	check_and_clear_labels(t_list *labels, char *code, int return_value)
{
	t_list		*tmp;
	t_deferred	*from_queue;
	int			n;

	while (labels)
	{
		if (((t_label*)labels->content)->addr == INT32_MAX)
			return_value = KO;
		else if (return_value == OK)
		{
			tmp = ((t_label*)labels->content)->queue;
			while (tmp)
			{
				from_queue = ((t_deferred*)tmp->content);
				n = ((t_label*)labels->content)->addr - from_queue->instr_addr;
				tobytes(&code[from_queue->dest_addr], n, from_queue->size);
				tmp = tmp->next;
			}
		}
		tmp = labels;
		labels = labels->next;
		ft_lstdelone(tmp, del_label);
	}
	return (return_value);
}

static int	set_new_label(t_list **labels, char *line, int addr)
{
	size_t	len;

	if (*line == '\0')
		return (OK);
	len = 0;
	while (*(line + len) && ft_strchr(LABEL_CHARS, *(line + len)))
		++len;
	if (!len || line[len] != LABEL_CHAR || !new_label(labels, line, len, addr))
		return (KO);
	while (line[++len] != '\0')
	{
		if (line[len] != ' ' && line[len] != '\t')
			return (KO);
	}
	return (OK);
}

static int	parse_exec_code(t_bot *bot, char *line, t_list **labels)
{
	char	*instr;
	int		addr;
	int		i;

	skip_whitespaces(&line);
	addr = bot->exec_code_size;
	i = 0;
	while (((t_op*)&g_op_tab[i])->name_len)
	{
		instr = line - 1;
		while ((instr = ft_strstr(instr + 1, ((t_op*)&g_op_tab[i])->name)))
		{
			if (get_instruction(bot, instr + ((t_op*)&g_op_tab[i])->name_len
			, labels, (t_op*)&g_op_tab[i]))
			{
				*instr = '\0';
				if (set_new_label(labels, line, addr) == OK)
					return (OK);
				*instr = ((t_op*)&g_op_tab[i])->name[0];
			}
			bot->exec_code_size = addr;
		}
		i += g_next_op_tab_elem;
	}
	return (set_new_label(labels, line, addr));
}

int			get_exec_code(t_bot *bot, size_t fd)
{
	char	*line;
	char	*tmp;
	t_list	*labels;

	labels = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if ((tmp = ft_strchr(line, '#')))
			*tmp = '\0';
		if (*line)
			if (parse_exec_code(bot, line, &labels) == KO)
			{
				free(line);
				return (check_and_clear_labels(labels, bot->exec_code, KO));
			}
		free(line);
	}
	if (bot->exec_code_size == 0)
		return (check_and_clear_labels(labels, bot->exec_code, KO));
	return (check_and_clear_labels(labels, bot->exec_code, OK));
}
