#include "unity.h"

#include "get_name_and_comment.h"

TEST_FILE("init_bot.c")
TEST_FILE("get_name_or_comment.c")

void setUp(void)
{
}

void tearDown(void)
{
}

void test_only_name_multiline(void)
{
    size_t	fd;
    t_bot	*bot;
    char	*line;

    fd = open("test/asm/bot_test.s", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    ft_putstr_fd(".name\t\"Sauce\nLisandra\"\n", fd);
    lseek(fd, 0, SEEK_SET);
    get_next_line(fd, &line);
    bot = init_bot();
    TEST_ASSERT_EQUAL_INT(KO, get_name_and_comment(bot, line, fd));
    ft_strdel(&line);
    close(fd);
    remove("test/asm/bot_test.s");
}

void test_nothing_after_name_and_comment(void)
{
    size_t	fd;
    t_bot	*bot;
    char	*line;

    fd = open("test/asm/bot_test.s", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    ft_putstr_fd(".name\t\"Sauce\"\n.comment\t\"Lisandra\"\n", fd);
    lseek(fd, 0, SEEK_SET);
    get_next_line(fd, &line);
    bot = init_bot();
    TEST_ASSERT_EQUAL_INT(KO, get_name_and_comment(bot, line, fd));
    ft_strdel(&line);
    close(fd);
    remove("test/asm/bot_test.s");
}
