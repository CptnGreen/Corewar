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

void test_only_name(void)
{
    size_t	fd;
    t_bot	*bot;
    char	*line;

    fd = open("test/asm/bot_test1.s", O_RDONLY);
    TEST_ASSERT_NOT_EQUAL_INT(-1, fd);
    get_next_line(fd, &line);
    bot = init_bot();
    get_name_and_comment(bot, line, fd);
    TEST_ASSERT_EQUAL_STRING("ololo", bot->name);
    TEST_ASSERT_EQUAL_STRING("ururu", bot->comment);
    close(fd);
}
