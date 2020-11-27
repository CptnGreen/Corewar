/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2020/11/27 12:05:39 by fcatina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				4096
# define IDX_MOD				512
# define CHAMP_MAX_SIZE			682

/*
** # define MEM_SIZE			(4 * 1024)
** # define IDX_MOD				(MEM_SIZE / 8)
** # define CHAMP_MAX_SIZE		(MEM_SIZE / 6)
*/

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

/*
** -----------------------------------------
*/

typedef char	t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

/*
** -----------------------------------------
*/

# define PROG_NAME_LENGTH		128
# define COMMENT_LENGTH			2048
# define COREWAR_EXEC_MAGIC	0xea83f3

typedef struct	s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	long			prog_size;
	char			comment[COMMENT_LENGTH + 1];
}				t_header;

typedef struct	s_op
{
	char	*name;
	int		name_len;
	int		arg_number;
	char	arg_types[3];
	char	order;
	int		cool_down;
	char	*definition;
	char	have_arg_type_code;
	char	is_dir_like_ind;
}				t_op;

/*
** const t_op	g_op_tab[17] =
** {
** 	{"live", 4, 1, {T_DIR}, 1, 10, "alive", 0, 0},
**	{"ld", 2, 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
**	{"st", 2, 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
**	{"add", 3, 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
**	{"sub", 3, 3, {T_REG, T_REG, T_REG}, 5, 10, "substraction", 1, 0},
**	{"and", 3, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
**		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
**	{"or", 2, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
**		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
**	{"xor", 3, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
**		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
**	{"zjmp", 4, 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
**	{"ldi", 3, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
**		"load index", 1, 1},
**	{"sti", 3, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
**		"store index", 1, 1},
**	{"fork", 4, 1, {T_DIR}, 12, 800, "fork", 0, 1},
**	{"lld", 3, 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
**	{"lldi", 4, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
**		"long load index", 1, 1},
**	{"lfork", 5, 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
**	{"aff", 3, 1, {T_REG}, 16, 2, "aff", 1, 0},
**	{0, 0, 0, {0}, 0, 0, 0, 0, 0}
** };
**
** const int	g_next_op_tab_elem = sizeof(t_op) / sizeof(t_op*);
**
** const char	g_arg_type_codes[4][4] =
** {
**	{0, 0, 0, 0},
**	{0, 64, 16, 4},
**	{0, 128, 32, 8},
**	{0, 192, 48, 12}
** };
*/

#endif
