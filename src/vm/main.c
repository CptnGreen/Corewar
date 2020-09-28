/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 22:40:51 by aimelda           #+#    #+#             */
/*   Updated: 2020/09/27 23:01:51 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define SUCCESS 0
#define FAILURE 1

static void	free_vm(t_vm *vm)
{
	ft_lstdel(&(vm->processes), free);
	free(vm);
}

static int	init_vm(void)
{
	t_vm	*vm;

	vm = (t_vm*)ft_memalloc(sizeof(t_vm));
	if (!vm)
	{
		perror("error");
		return (KO);
	}
	vm->dump = -1;
	return (OK);
}

int			main(int argc, char **argv)
{
	t_vm	*vm;
	int		return_value;

	if ((vm = init_vm()) == KO
	|| validation(vm, argc, argv) == KO
	|| fighting(vm) == KO)
		return_value = FAILURE;
	else
		return_value = SUCCESS;
	free_vm(vm);
	return (return_value);
}