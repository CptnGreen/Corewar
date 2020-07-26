#include "unity.h"

#include "get_name_or_comment.h"

TEST_FILE("init_bot.c")

void setUp(void)
{
}

void tearDown(void)
{
}

void test_name_oneline(void)
{
    t_bot	*bot;
    char	line[] = ".name\t\"ololo\"";

    bot = init_bot();
    get_name_or_comment(bot->name, line, 0);
    TEST_ASSERT_EQUAL_STRING("ololo", bot->name);
    TEST_ASSERT_EQUAL_STRING("", bot->comment);
}

void test_comment_oneline(void)
{
    t_bot	*bot;
    char	line[] = ".comment\t\"ururu\"";

    bot = init_bot();
    get_name_or_comment(bot->comment, line, 0);
    TEST_ASSERT_EQUAL_STRING("ururu", bot->comment);
    TEST_ASSERT_EQUAL_STRING("", bot->name);
}

void test_name_multiline(void)
{
    size_t	fd;
    t_bot	*bot;
    char	*line;

    fd = open("test/asm/bot_test1.s", O_RDONLY);
    TEST_ASSERT_NOT_EQUAL_INT(-1, fd);
    get_next_line(fd, &line);
    bot = init_bot();
    get_name_or_comment(bot->name, line, fd);
    TEST_ASSERT_EQUAL_STRING("Sauce\nLisandra", bot->name);
    close(fd);
}

void test_comment_multiline(void)
{
    TEST_IGNORE_MESSAGE("Need to implement");
}
