/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slisandr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 03:59:47 by aimelda           #+#    #+#             */
/*   Updated: 2020/11/28 12:19:10 by slisandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Two identical copies of this file are present at src/asm and src/vm
*/

#ifndef OP_C
# define OP_C

# include "corewar.h"

const t_op	g_op_tab[17] =
{
	{"live", 4, 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, 3, {T_REG, T_REG, T_REG}, 5, 10, "substraction", 1, 0},
	{"and", 3, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 2, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 4, 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 4, 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 3, 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 4, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 5, 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 3, 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, 0, {0}, 0, 0, 0, 0, 0}
};

const char	g_arg_type_codes[4][4] =
{
	{0, 0, 0, 0},
	{0, 64, 16, 4},
	{0, 128, 32, 8},
	{0, 192, 48, 12}
};

#endif
