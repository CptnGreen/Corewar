/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aimelda <aimelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 22:40:51 by aimelda           #+#    #+#             */
/*   Updated: 2020/09/28 16:56:41 by aimelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	free_vm(t_vm *vm)
{
	ft_lstdel(&(vm->processes), free);
	free(vm);
}

static t_vm	*init_vm()
{
	t_vm	*vm;

	vm = (t_vm*)ft_memalloc(sizeof(t_vm));
	if (!vm)
	{
		perror("error");
		return (NULL);
	}
	vm->dump = -1;
	return (vm);
}

int			main(int argc, char **argv)
{
	t_vm	*vm;
	int		return_value;

	if ((vm = init_vm()) == KO
	|| validation(vm, argc, argv) == KO
	|| fighting(vm) == KO)
		return_value = EXIT_FAILURE;
	else
		return_value = EXIT_SUCCESS;
	free_vm(vm);
	return (return_value);
}
