/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 13:49:32 by aimelda           #+#    #+#             */
/*   Updated: 2020/07/30 15:12:56 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	del_label(void *node, size_t content_size)
{
	free(((t_label*)node)->name);
	ft_lstdel(&(((t_label*)node)->queue), NULL);
}

static int	check_and_clear_labels(t_list *labels, char *code, int return_value)
{
	t_list	*tmp;
	long	n;

	while (labels)
	{
		if (!((t_label*)labels->content)->addr)
			return_value = KO;
		else if (return_value == OK)
		{
			tmp = ((t_label*)labels->content)->queue;
			while (tmp)
			{
				n = (((t_label*)labels->content)->addr - (long)tmp->content);
				while (tmp->content_size--)
					code[(long)tmp->content++] = (char*)(&n)[tmp->content_size];
				tmp = tmp->next;
			}
		}
		tmp = labels;
		labels = labels->next;
		ft_lstdelone(&tmp, del_label);
	}
	return (return_value);
}

static int	get_new_label(t_list **labels, char *line, long addr)
{
	t_label	*new_label;
	size_t	len;

	len = ft_strlen(line);
	while (line[len - 1] == ' ' || line[len - 1] == '\t') // what about other whitespaces?
		--len;
	if (len <= 1 || line[len - 1] != LABEL_CHAR
	|| !(new_label = (t_label*)malloc(sizeof(t_label)))
	|| !(new_label->name = (char*)malloc(len)))
		return (KO);
	new_label->name[--len] = '\0';
	while (len--)
		if (ft_strchr(LABEL_CHARS, line[len]))
			new_label->name[len] = line[len];
		else
			return (KO);
	new_label->addr = addr;
	new_label->queue = NULL;
	return (OK);
}

static int	parse_exec_code(t_bot *bot, char *line, t_list **labels)
{
    char	*tmp;
	char	*instruction;
	long	addr;
	int		i;

    while (*line == ' ' || *line == '\t') // what about other whitespaces?
        ++line;
    if ((tmp = ft_strchr(line, '#')))
        *tmp = '\0';
	instruction = line - 1;
	addr = bot->exec_code_size;
	i = 0;
	while (g_op_tab[i]->name)
	{
		while ((instruction = ft_strstr(instruction + 1, g_op_tab[i]->name)))
			if (get_instruction(bot, instruction, *labels, g_op_tab[i - 1]))
			{
				*instruction = '\0';
				return (get_new_label(labels, line, addr));
			}
		++i;
	}
	return (get_new_label(labels, line, addr));
}

int			*get_exec_code(t_bot *bot, size_t fd)
{
	char	*line;
	t_list	*labels;

	labels = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (*line && *line != '#')
			if (parse_exec_code(bot, line, &labels) == KO)
				return (check_and_clear_labels(labels, bot->exec_code, KO));
		free(line);
	}
	if (bot->exec_code_size == 0)
		return (check_and_clear_labels(labels, bot->exec_code, KO));
	return (check_and_clear_labels(labels, bot->exec_code, OK));
}
