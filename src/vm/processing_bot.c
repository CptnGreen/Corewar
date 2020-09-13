#include "corewar.h"

int processing_bot(t_bot *bot)
{
	int fd;
	int r;
	char *cur;

	r = 0;
	fd = 0;

	if (!(bot = (t_bot*)malloc(sizeof(t_bot))))
		error("fdv");
	if (fd = open(bot,O_RDONLY) == -1)
		error("err");
	if(r = read(fd, &cur, PROG_NAME_LENGTH + COMMENT_LENGTH) < 0)
		error("err");
	if (ft_strncmp(cur, MAGIC_HEADER, EXEC_CODE_INT) != 0)
			error("err");
		cur = cur +4;
	ft_memcpy(bot->name,cur,PROG_NAME_LENGTH);
			cur = cur + PROG_NAME_LENGTH;

		ft_memcpy(bot->comment,cur,COMMENT_LENGTH);
		cur = cur + COMMENT_LENGTH;
	if(r = read(fd, &cur, CHAMP_MAX_SIZE + INSTRUCTION_MAX_SIZE)< 0)
		error("error");
	ft_memcpy(bot->exec_code,cur,EXEC_CODE_INT);
	if(!r == bot->exec_code)
		error("gfdgd");
	close(fd);
	free(cur);
}