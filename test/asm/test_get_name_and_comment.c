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

/*
** In tests below function must return OK:
*/

void test_valid_name_oneline_comment_oneline(void)
{
    size_t	fd;
    t_bot	*bot;

    fd = open("test/asm/bot_test.s", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    ft_putstr_fd(".name\t\"Sauce\"\n.comment\t\"Lisandra\"\nSOME TEXT\n", fd);
    lseek(fd, 0, SEEK_SET);
    bot = init_bot();
    TEST_ASSERT_EQUAL_INT(OK, get_name_and_comment(bot, fd));
    TEST_ASSERT_EQUAL_STRING("Sauce", bot->name);
    TEST_ASSERT_EQUAL_STRING("Lisandra", bot->comment);
    close(fd);
    remove("test/asm/bot_test.s");
}

void test_valid_empty_lines_between_name_and_comment(void)
{
    size_t	fd;
    t_bot	*bot;

    fd = open("test/asm/bot_test.s", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    ft_putstr_fd(".name\t\"Sauce\"\n\n\n\n.comment\t\"Lisandra\"\nSOME TEXT\n", fd);
    lseek(fd, 0, SEEK_SET);
    bot = init_bot();
    TEST_ASSERT_EQUAL_INT(OK, get_name_and_comment(bot, fd));
    TEST_ASSERT_EQUAL_STRING("Sauce", bot->name);
    TEST_ASSERT_EQUAL_STRING("Lisandra", bot->comment);
    close(fd);
    remove("test/asm/bot_test.s");
}

/*
** In situations below function must return KO:
*/

void test_name_garbage_after(void)
{
    size_t	fd;
    t_bot	*bot;

    fd = open("test/asm/bot_test.s", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    ft_putstr_fd(".name\t\"Sauce\" GARBAGE\n.comment\t\"Lisandra\"\nSOME TEXT\n", fd);
    lseek(fd, 0, SEEK_SET);
    bot = init_bot();
    TEST_ASSERT_EQUAL_INT(KO, get_name_and_comment(bot, fd));
    close(fd);
    remove("test/asm/bot_test.s");
}

void test_name_garbage_between(void)
{
    size_t	fd;
    t_bot	*bot;

    fd = open("test/asm/bot_test.s", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    ft_putstr_fd(".name\tGARBAGE\t\"Sauce\"\n.comment\t\"Lisandra\"\nSOME TEXT\n", fd);
    lseek(fd, 0, SEEK_SET);
    bot = init_bot();
    TEST_ASSERT_EQUAL_INT(KO, get_name_and_comment(bot, fd));
    close(fd);
    remove("test/asm/bot_test.s");
}

void test_only_name_multiline(void)
{
    size_t	fd;
    t_bot	*bot;

    fd = open("test/asm/bot_test.s", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    ft_putstr_fd(".name\t\"Sauce\nLisandra\"\n", fd);
    lseek(fd, 0, SEEK_SET);
    bot = init_bot();
    TEST_ASSERT_EQUAL_INT(KO, get_name_and_comment(bot, fd));
    close(fd);
    remove("test/asm/bot_test.s");
}
