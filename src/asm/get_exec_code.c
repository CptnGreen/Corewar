/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 13:49:32 by aimelda           #+#    #+#             */
/*   Updated: 2020/07/28 20:38:14 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void handle_code(t_bot *bot, char *line)
{
    char    *tmp;

    while (*line == ' ' || *line == '\t') // what about other whitespaces?
        ++line;
    if ((tmp = ft_strchr(line, '#')))
        *tmp = '\0';
}

int    *get_exec_code(t_bot *bot, size_t fd)
{
    char    *line;

    while (get_next_line(fd, &line) > 0)
    {
        if (*line && *line != '#')
            handle_code(bot, line);
        free(line);
    }
    if (bot->exec_code_size)
        return (OK);
    return (KO);
}
