/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slisandr <slisandr@student.21-s~.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 22:40:51 by aimelda           #+#    #+#             */
/*   Updated: 2020/11/01 21:46:10 by slisandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	free_vm(t_vm *vm)
{
	int		i;

	i = MAX_PLAYERS;
	while (i--)
		free(vm->players[i]);
	ft_lstdel(&(vm->processes), free);
}

static void	init_vm(t_vm *vm)
{
	ft_bzero(vm, sizeof(t_vm));
	vm->dump = -1;
}

int			main(int argc, char **argv)
{
	t_vm	vm;
	int		return_value;

	init_vm(&vm);
	if (validation(&vm, argc, argv) == KO
	|| fighting(&vm) == KO)
		return_value = EXIT_FAILURE;
	else
		return_value = EXIT_SUCCESS;
	free_vm(&vm);
	return (return_value);
}
