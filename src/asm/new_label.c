/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slisandr <slisandr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 00:19:18 by aimelda           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/09/24 22:19:32 by slisandr         ###   ########.fr       */
=======
/*   Updated: 2020/09/28 16:53:54 by aimelda          ###   ########.fr       */
>>>>>>> 00cb53e4f8f6b75f18a73f5bb14369d573328e4c
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_list	*is_exist(t_list *node, char *name, size_t len, int addr)
{
	while (node)
	{
		if (ft_strlen(((t_label *)node->content)->name) == len &&
			!ft_strncmp(((t_label *)node->content)->name, name, len))
		{
			if (((t_label*)node->content)->addr == INT32_MAX)
				((t_label*)node->content)->addr = addr;
			return (node);
		}
		node = node->next;
	}
	return (NULL);
}

t_label			*new_label(t_list **label, char *name, size_t len, int addr)
{
	t_list	*node;

	if ((node = is_exist(*label, name, len, addr)))
		return (node->content);
	if (!(node = ft_lstnew(NULL)))
		return (NULL);
	ft_lstadd(label, node);
	if (!(node->content = malloc(sizeof(t_label))) ||
		!(((t_label *)node->content)->name = (char *)malloc(len + 1)))
		return (NULL);
	ft_strncpy(((t_label*)node->content)->name, name, len);
	((t_label*)node->content)->name[len] = '\0';
	((t_label*)node->content)->addr = addr;
	((t_label*)node->content)->queue = NULL;
	return (node->content);
}
