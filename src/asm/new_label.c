/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 00:19:18 by aimelda           #+#    #+#             */
/*   Updated: 2020/08/06 08:32:05 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern char	g_codes_of_arg_type[4][4];

static t_list	*is_exist(t_list *node, char *name, size_t len, int addr)
{
	while (node)
	{
		if (ft_strlen(((t_label*)node->content)->name) == len
		&& !ft_strncmp(((t_label*)node->content)->name, name, len))
		{
			if (((t_label*)node->content)->addr == INT32_MAX)
				((t_label*)node->content)->addr = addr;
			return (node);
		}
		node = node->next;
	}
	return (NULL);
}

t_label			*new_label(t_list **label, char *name, size_t len, int addr, int log_fd)
{
	t_list	*node;

	if ((node = is_exist(*label, name, len, addr)))
		return (node->content);
	if (!(node = ft_lstnew(NULL)))
	{
		ft_putstr_fd("new_label(): 1\n", log_fd);
		return (NULL);
	}
	ft_lstadd(label, node);
	if (!(node->content = malloc(sizeof(t_label)))
	|| !(((t_label*)node->content)->name = (char*)malloc(len + 1)))
	{
		ft_putstr_fd("new_label(): 2\n", log_fd);
		return (NULL);
	}
	ft_strncpy(((t_label*)node->content)->name, name, len);
	((t_label*)node->content)->name[len] = '\0';
	((t_label*)node->content)->addr = addr;
	((t_label*)node->content)->queue = NULL;
	return (node->content);
}
