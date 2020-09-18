#include "corewar.h"

#define MAGIC_HEADER_SIZE 4
#define DIV_ZEROES_SIZE 4
#define EXEC_CODE_SIZE_SIZE 4
#define BUFFER_SIZE MAGIC_HEADER_SIZE + PROG_NAME_LENGTH + DIV_ZEROES_SIZE \
		+ EXEC_CODE_SIZE_SIZE + COMMENT_LENGTH + DIV_ZEROES_SIZE
#define OPEN_READ_ERROR_CODE -1

int	error(void)
{
	// error message
	return (KO);
}

int processing_bot(t_bot *bot, char *file_name)
{
	int		fd;
	int		actual_exec_code_size;
	char	buffer[BUFFER_SIZE + 1];
	char	*buf_ptr;

	if (!(bot = (t_bot*)malloc(sizeof(t_bot))))
		return error(); // "error: errno"
	if (fd = open(file_name, O_RDONLY) == OPEN_READ_ERROR_CODE)
		return error(); // "error: errno"
	if (read(fd, &buffer, BUFFER_SIZE) < BUFFER_SIZE) // if read = -1
		return error(); // "error: file [file_name] is invalid"
	buf_ptr = buffer;
	if (ft_strncmp(buf_ptr, MAGIC_HEADER, MAGIC_HEADER_SIZE) != 0)
		return error(); // "error: incorrect magic header"
	buf_ptr += MAGIC_HEADER_SIZE;
	ft_memcpy(bot->name, buf_ptr, PROG_NAME_LENGTH);
	buf_ptr += PROG_NAME_LENGTH + DIV_ZEROES_SIZE;
	ft_memcpy(bot->exec_code_size, buf_ptr, EXEC_CODE_SIZE_SIZE);
	buf_ptr += EXEC_CODE_SIZE_SIZE;
	ft_memcpy(bot->comment, buf_ptr, COMMENT_LENGTH);
	actual_exec_code_size = read(fd, &buffer, CHAMP_MAX_SIZE + 1); // if read = -1 || if > CHAMP_MAX_SIZE
	if (actual_exec_code_size != bot->exec_code_size)
		return error(); // "error: player's actual execution code size doesn't match with the declared size."
	ft_memcpy(bot->exec_code, buffer, bot->exec_code_size);
	close(fd);
	return (OK);
}