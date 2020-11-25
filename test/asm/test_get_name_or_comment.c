#include "unity.h"
#include "sys/stat.h"

#include "get_name_or_comment.h"

TEST_FILE("init_bot.c")
TEST_FILE("free.c")

void setUp(void)
{
}

void tearDown(void)
{
}

void test_name_oneline(void)
{
	t_bot	*bot;
	char	line[] = "\"ololo\"";

	bot = (t_bot *)ft_memalloc(sizeof(t_bot));
	TEST_ASSERT_EQUAL_INT(OK, get_name_or_comment(bot->name, PROG_NAME_LENGTH, line, 0));
	TEST_ASSERT_EQUAL_STRING("ololo", bot->name);
	TEST_ASSERT_EQUAL_STRING("", bot->comment);
	free(bot);
}

void test_name_oneline_endline_whitespaces(void)
{
	t_bot	*bot;
	char	line[] = "\"ololo\"   \t    \t   ";

	bot = (t_bot *)ft_memalloc(sizeof(t_bot));
	TEST_ASSERT_EQUAL_INT(OK, get_name_or_comment(bot->name, PROG_NAME_LENGTH, line, 0));
	TEST_ASSERT_EQUAL_STRING("ololo", bot->name);
	TEST_ASSERT_EQUAL_STRING("", bot->comment);
	free(bot);
}

void test_name_oneline_endline_comment(void)
{
	t_bot	*bot;
	char	line[] = "\"ololo\" # SOME COMMENT";

	bot = (t_bot *)ft_memalloc(sizeof(t_bot));
	TEST_ASSERT_EQUAL_INT(OK, get_name_or_comment(bot->name, PROG_NAME_LENGTH, line, 0));
	TEST_ASSERT_EQUAL_STRING("ololo", bot->name);
	TEST_ASSERT_EQUAL_STRING("", bot->comment);
	free(bot);
}

void test_comment_oneline(void)
{
	t_bot	*bot;
	char	line[] = "\"ururu\"";

	bot = (t_bot *)ft_memalloc(sizeof(t_bot));
	TEST_ASSERT_EQUAL_INT(OK, get_name_or_comment(bot->comment, COMMENT_LENGTH, line, 0));
	TEST_ASSERT_EQUAL_STRING("ururu", bot->comment);
	TEST_ASSERT_EQUAL_STRING("", bot->name);
	free(bot);
}

void test_name_multiline(void)
{
	size_t	fd;
	t_bot	*bot;
	char	*line;

	fd = open("test/asm/bot_test.s", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	ft_putstr_fd("\"Sauce\nLisandra\"\n", fd);
	lseek(fd, 0, SEEK_SET);
	get_next_line(fd, &line);
	bot = (t_bot *)ft_memalloc(sizeof(t_bot));
	TEST_ASSERT_EQUAL_INT(OK, get_name_or_comment(bot->name, PROG_NAME_LENGTH, line, fd));
	TEST_ASSERT_EQUAL_STRING("Sauce\nLisandra", bot->name);
	TEST_ASSERT_EQUAL_STRING("", bot->comment);
	free(bot);
	ft_strdel(&line);
	close(fd);
	remove("test/asm/bot_test.s");
}

/*
** The line in this test contatins 129 characters which is too much:
*/

void test_name_too_ololong(void)
{
	t_bot	*bot;
	char	line[] = "\"ololololololololololololololololololololololololololololololololololololololololololololololololololololololololololololololololo\"";

	bot = (t_bot *)ft_memalloc(sizeof(t_bot));
	TEST_ASSERT_EQUAL_INT(KO, get_name_or_comment(bot->name, PROG_NAME_LENGTH, line, 0));
	TEST_ASSERT_EQUAL_STRING("", bot->name);
	TEST_ASSERT_EQUAL_STRING("", bot->comment);
	free(bot);
}

void test_name_too_ololong_multiline(void)
{
	size_t	fd;
	t_bot	*bot;
	char	*line;

	fd = open("test/asm/bot_test.s", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	/*
	** There are 132 characters in the name string below,
	** 4 newlines among them; one newline is '\' + 'n' so gives 2 letters,
	** hence you get 132 - 4 = 128 real symbols (including newlines)
	** so function must return OK
	*/
	ft_putstr_fd("\"ololololo\nlolololololololololololo\nlolololololololololololololololololololololololololololololololololololo\nlololololololo\nlolol\"", fd);
	lseek(fd, 0, SEEK_SET);
	get_next_line(fd, &line);
	bot = (t_bot *)ft_memalloc(sizeof(t_bot));
	TEST_ASSERT_EQUAL_INT(OK, get_name_or_comment(bot->name, PROG_NAME_LENGTH, line, fd));
	TEST_ASSERT_EQUAL_STRING("ololololo\nlolololololololololololo\nlolololololololololololololololololololololololololololololololololololo\nlololololololo\nlolol", bot->name);
	TEST_ASSERT_EQUAL_STRING("", bot->comment);
	free(bot);
	ft_strdel(&line);
	close(fd);
	remove("test/asm/bot_test.s");
}
