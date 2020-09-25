/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 15:29:39 by aimelda           #+#    #+#             */
/*   Updated: 2020/09/24 18:28:01 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define MAGIC_HEADER_SIZE 4
#define DIV_ZEROES_SIZE 4
#define EXEC_CODE_SIZE_SIZE 4
#define BUFFER_SIZE MAGIC_HEADER_SIZE + PROG_NAME_LENGTH + DIV_ZEROES_SIZE + EXEC_CODE_SIZE_SIZE + COMMENT_LENGTH + DIV_ZEROES_SIZE

static int	error(char *str)
{
	if (str)
	{
		ft_printf("error: %s", str);
		free(str);
	}
	else
		perror("error");
	return (KO);
}

static int	is_correct(char *file_name, int actual_size, int declared_size)
{
	if (actual_size == -1)
		return (error(NULL));
	if (actual_size > CHAMP_MAX_SIZE)
		return (error(ft_strjoin(file_name, " has too large code size.")));
	if (actual_size != declared_size)
		return (error(ft_strjoin(file_name, ": actual execution code size doesn't match with the declared size.")));
	return (OK);
}

static int	parse_bot(t_bot **bot, char *file_name)
{
	int		fd;
	char	buffer[BUFFER_SIZE + 1];
	char	*buf_ptr;

	if (!(*bot = (t_bot*)malloc(sizeof(t_bot)))
	|| (fd = open(file_name, O_RDONLY) == -1))
		return (error(NULL));
	if (read(fd, &buffer, BUFFER_SIZE) < BUFFER_SIZE)
		return (error(ft_strjoin(file_name, " is too small.")));
	buf_ptr = buffer;
	if (ft_strncmp(buf_ptr, MAGIC_HEADER, MAGIC_HEADER_SIZE) != 0)
		return (error(ft_strjoin(file_name, " has incorrect magic header.")));
	buf_ptr += MAGIC_HEADER_SIZE;
	ft_memcpy((*bot)->name, buf_ptr, PROG_NAME_LENGTH);
	buf_ptr += PROG_NAME_LENGTH + DIV_ZEROES_SIZE;
	ft_memcpy((*bot)->exec_code_size, buf_ptr, EXEC_CODE_SIZE_SIZE);
	buf_ptr += EXEC_CODE_SIZE_SIZE;
	ft_memcpy((*bot)->comment, buf_ptr, COMMENT_LENGTH);
	if (is_correct(file_name, read(fd, &buffer, CHAMP_MAX_SIZE + 1)
	, (*bot)->exec_code_size) == KO)
		return (KO);
	ft_memcpy((*bot)->exec_code, buffer, (*bot)->exec_code_size);
	close(fd);
	return (OK);
}

int			bot_processing(t_vm *vm, t_list **players, int order, char *file)
{
	t_list	*tmp;

	if (order == 0)
	{
		if (!(tmp = ft_lstnew(NULL)))
			return (error(NULL));
		ft_lstadd(players, tmp);
		return (parse_bot(&((*players)->content), file));
	}
	else if (vm->players[order] == NULL)
		return (parse_bot(&(vm->players[order]), file));
	ft_printf("error: two or more players are assigned the same number.");
	return (KO);
}
