/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_exec_code.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slisandr <slisandr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 12:52:04 by slisandr          #+#    #+#             */
/*   Updated: 2020/10/25 01:42:52 by slisandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"

#include "get_exec_code.h"
#include "sys/stat.h"

TEST_FILE("init_bot.c")
TEST_FILE("get_instruction.c")
TEST_FILE("tobytes.c")
TEST_FILE("skip_whitespaces.c")
TEST_FILE("new_label.c")
TEST_FILE("get_number.c")
TEST_FILE("get_name_and_comment.c")
TEST_FILE("get_name_or_comment.c")
TEST_FILE("op.c")

void setUp(void)
{
}

void tearDown(void)
{
}

/*
** Valid test cases
*/

void test_valid_from_brazhnik(void)
{
    size_t	fd;
    t_bot	*bot;

    // TEST_IGNORE_MESSAGE("Skip for now");
    fd = open("test/asm/bot_test.s", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    TEST_ASSERT_NOT_EQUAL_INT(-1, fd);
    ft_putstr_fd("loop:\n\t\tsti r1, %:live, %1\nlive:\n\t\tlive %0\n\t\tld %0, r2\n\t\tzjmp %:loop\n", fd);
    lseek(fd, 0, SEEK_SET);
    bot = (t_bot *)ft_memalloc(sizeof(t_bot));
    TEST_ASSERT_NOT_NULL(bot);
    TEST_ASSERT_EQUAL_INT(OK, get_exec_code(bot, fd));
    TEST_ASSERT_EQUAL_INT(22, bot->exec_code_size);
    TEST_ASSERT_EQUAL_INT8_ARRAY("\x0b\x68\x01\x00\x07\x00\x01\x01\x00\x00\x00\x00\x02\x90\x00\x00\x00\x00\x02\x09\xff\xed", bot->exec_code, bot->exec_code_size);
    close(fd);
    remove("test/asm/bot_test.s");
}

void test_valid_more_whitespaces(void)
{
    size_t	fd;
    t_bot	*bot;

    // TEST_IGNORE_MESSAGE("Skip for now");
    fd = open("test/asm/bot_test.s", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    TEST_ASSERT_NOT_EQUAL_INT(-1, fd);
    ft_putstr_fd("tir:	sti	r1,%:tirb,%1\n\tld	%123 ,r10#comment\n\tld	%1   ,  r1\n  #so  \n\tld	%0,r11\n\n\n\ntirb:	live	%1\n", fd);
    lseek(fd, 0, SEEK_SET);
    bot = (t_bot *)ft_memalloc(sizeof(t_bot));
    TEST_ASSERT_NOT_NULL(bot);
    TEST_ASSERT_EQUAL_INT(OK, get_exec_code(bot, fd));
    TEST_ASSERT_EQUAL_INT(33, bot->exec_code_size);
    TEST_ASSERT_EQUAL_INT8_ARRAY("\x0b\x68\x01\x00\x1c\x00\x01\x02\x90\x00\x00\x00\x7b\x0a\x02\x90\x00\x00\x00\x01\x01\x02\x90\x00\x00\x00\x00\x0b\x01\x00\x00\x00\x01", bot->exec_code, bot->exec_code_size);
    close(fd);
    remove("test/asm/bot_test.s");
}

void test_valid_label_points_two_addresses(void)
{
    size_t	fd;
    t_bot	*bot;

    // TEST_IGNORE_MESSAGE("Skip for now");
    fd = open("test/asm/bot_test.s", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    TEST_ASSERT_NOT_EQUAL_INT(-1, fd);
    ft_putstr_fd("tir:	sti	r1,%:tirb,%1\n\tld	%123 ,r10\n\tld	%1   ,  r1\n\n\n \t  tirb:\n\n\n\tld	%0,r11\n\n\n\ntirb:	live	%1\n", fd);
    lseek(fd, 0, SEEK_SET);
    bot = (t_bot *)ft_memalloc(sizeof(t_bot));
    TEST_ASSERT_NOT_NULL(bot);
    TEST_ASSERT_EQUAL_INT(OK, get_exec_code(bot, fd));
    TEST_ASSERT_EQUAL_INT(33, bot->exec_code_size);
    TEST_ASSERT_EQUAL_INT8_ARRAY("\x0b\x68\x01\x00\x15\x00\x01\x02\x90\x00\x00\x00\x7b\x0a\x02\x90\x00\x00\x00\x01\x01\x02\x90\x00\x00\x00\x00\x0b\x01\x00\x00\x00\x01", bot->exec_code, bot->exec_code_size);
    close(fd);
    remove("test/asm/bot_test.s");
}

void test_valid_big_numbers_and_same_names(void)
{
    size_t	fd;
    t_bot	*bot;

    // TEST_IGNORE_MESSAGE("Skip for now");
    fd = open("test/asm/bot_test.s", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    TEST_ASSERT_NOT_EQUAL_INT(-1, fd);
    ft_putstr_fd("fork:	 fork  %:forka #fork\nforka:      sti r1, %:fork, %-10000000000000000000000\nsti r1, %:fork, %543546576345767642342345625\n", fd);
    lseek(fd, 0, SEEK_SET);
    bot = (t_bot *)ft_memalloc(sizeof(t_bot));
    TEST_ASSERT_NOT_NULL(bot);
    TEST_ASSERT_EQUAL_INT(OK, get_exec_code(bot, fd));
    TEST_ASSERT_EQUAL_INT(17, bot->exec_code_size);
    TEST_ASSERT_EQUAL_INT8_ARRAY("\x0c\x00\x03\x0b\x68\x01\xff\xfd\x00\x00\x0b\x68\x01\xff\xf6\xff\xff", bot->exec_code, bot->exec_code_size);
    close(fd);
    remove("test/asm/bot_test.s");
}

void test_valid_bot_car_from_champs(void)
{
    size_t	fd;
    t_bot	*bot;
    int     res;

    // TEST_IGNORE_MESSAGE("Skip for now");
    fd = open("resources/vm_champs/champs/Car.s", O_RDONLY);
    TEST_ASSERT_NOT_EQUAL_INT(-1, fd);
    lseek(fd, 0, SEEK_SET);
    bot = (t_bot *)ft_memalloc(sizeof(t_bot));
    TEST_ASSERT_NOT_NULL(bot);
    TEST_ASSERT_EQUAL_INT(OK, get_name_and_comment(bot, fd));
    TEST_ASSERT_EQUAL_INT(OK, get_exec_code(bot, fd));
    TEST_ASSERT_EQUAL_INT(281, bot->exec_code_size);
    TEST_ASSERT_EQUAL_INT8_ARRAY("\x0c\x00\x6a\x02\x90\xff\xff\xfe\xf0\x03\x01\x00\x00\x00\x00\x0c\x00\x2f\x02\x90\xff\xff\xfe\xf0\x03\x0c\x00\x14\x02\x90\x00\x00\x00\x00\x02\x02\x90\x00\x00\x00\x00\x04\x09\x00\x8b\x02\x90\x00\x00\x00\x04\x02\x02\x90\x00\x00\x00\x00\x04\x09\x00\x7a\x02\x90\xff\xff\xff\x36\x03\x0c\x00\x14\x02\x90\x00\x00\x00\x00\x02\x02\x90\x00\x00\x00\x00\x04\x09\x00\x93\x02\x90\x00\x00\x00\x04\x02\x02\x90\x00\x00\x00\x00\x04\x09\x00\x82\x02\x90\x00\x00\x01\x90\x03\x01\x00\x00\x00\x00\x0c\x00\x28\x0c\x00\x14\x02\x90\x00\x00\x00\x00\x02\x02\x90\x00\x00\x00\x00\x04\x09\x00\x45\x02\x90\x00\x00\x00\x04\x02\x02\x90\x00\x00\x00\x00\x04\x09\x00\x34\x0c\x00\x0d\x02\x90\x00\x00\x00\x00\x04\x09\x00\x5b\x02\x90\x00\x00\x00\x00\x04\x09\x00\x5c\x0a\x64\x02\x00\x12\x06\x02\x90\x00\x00\x00\x00\x04\x01\x00\x00\x00\x01\x0b\x54\x06\x02\x03\x09\xfe\xeb\x0a\x64\x02\x00\x12\x06\x02\x90\x00\x00\x00\x00\x04\x01\x00\x00\x00\x01\x0b\x54\x06\x02\x03\x09\x01\x8b\x0a\x64\x02\x00\x12\x06\x02\x90\x00\x00\x00\x00\x04\x01\x00\x00\x00\x01\x0b\x54\x06\x02\x03\x09\xff\x31\x01\x00\x00\x00\x01\x0c\xff\xfb\x09\xff\xf8\x01\x00\x00\x00\x01\x0c\xff\xfb\x09\xff\xf8", bot->exec_code, 281);
    close(fd);
}

/*
** Invalid test cases
*/

void test_invalid_nonexistent_label(void)
{
    size_t	fd;
    t_bot	*bot;

    // TEST_IGNORE_MESSAGE("Skip for now");
    fd = open("test/asm/bot_test.s", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    TEST_ASSERT_NOT_EQUAL_INT(-1, fd);
    ft_putstr_fd("tir:	sti	r1,%:tirb,%1\n\tld	%123 ,r10\n\tld	%1   ,  r1\n\tld	%0,r11\n", fd);
    lseek(fd, 0, SEEK_SET);
    bot = (t_bot *)ft_memalloc(sizeof(t_bot));
    TEST_ASSERT_NOT_NULL(bot);
    TEST_ASSERT_EQUAL_INT(KO, get_exec_code(bot, fd));
    close(fd);
    remove("test/asm/bot_test.s");
}

void test_invalid_extra_symbol(void)
{
    size_t	fd;
    t_bot	*bot;

    // TEST_IGNORE_MESSAGE("Skip for now");
    fd = open("test/asm/bot_test.s", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    TEST_ASSERT_NOT_EQUAL_INT(-1, fd);
    ft_putstr_fd("tir:	sti	r1,%:tirb,%1    s\n\ntirb:	live	%1", fd);
    lseek(fd, 0, SEEK_SET);
    bot = (t_bot *)ft_memalloc(sizeof(t_bot));
    TEST_ASSERT_NOT_NULL(bot);
    TEST_ASSERT_EQUAL_INT(KO, get_exec_code(bot, fd));
    close(fd);
    remove("test/asm/bot_test.s");
}

void test_invalid_no_instruction(void)
{
    size_t	fd;
    t_bot	*bot;

    // TEST_IGNORE_MESSAGE("Skip for now");
    fd = open("test/asm/bot_test.s", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    TEST_ASSERT_NOT_EQUAL_INT(-1, fd);
    ft_putstr_fd("", fd);
    lseek(fd, 0, SEEK_SET);
    bot = (t_bot *)ft_memalloc(sizeof(t_bot));
    TEST_ASSERT_NOT_NULL(bot);
    TEST_ASSERT_EQUAL_INT(KO, get_exec_code(bot, fd));
    close(fd);
    remove("test/asm/bot_test.s");
}

void test_invalid_no_instruction_only_comment(void)
{
    size_t	fd;
    t_bot	*bot;

    // TEST_IGNORE_MESSAGE("Skip for now");
    fd = open("test/asm/bot_test.s", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    TEST_ASSERT_NOT_EQUAL_INT(-1, fd);
    ft_putstr_fd(" #comment\n", fd);
    lseek(fd, 0, SEEK_SET);
    bot = (t_bot *)ft_memalloc(sizeof(t_bot));
    TEST_ASSERT_NOT_NULL(bot);
    TEST_ASSERT_EQUAL_INT(KO, get_exec_code(bot, fd));
    close(fd);
    remove("test/asm/bot_test.s");
}

void test_invalid_missed_number(void)
{
    size_t	fd;
    t_bot	*bot;

    // TEST_IGNORE_MESSAGE("Skip for now");
    fd = open("test/asm/bot_test.s", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    TEST_ASSERT_NOT_EQUAL_INT(-1, fd);
    ft_putstr_fd("fork:	 fork  %:forka #fork\nforka:      sti r1, %, %5\nsti r1, %:fork, %5\n", fd);
    lseek(fd, 0, SEEK_SET);
    bot = (t_bot *)ft_memalloc(sizeof(t_bot));
    TEST_ASSERT_NOT_NULL(bot);
    TEST_ASSERT_EQUAL_INT(KO, get_exec_code(bot, fd));
    close(fd);
    remove("test/asm/bot_test.s");
}

void test_invalid_separator_char_at_the_end_of_instruction(void)
{
    size_t	fd;
    t_bot	*bot;

    // TEST_IGNORE_MESSAGE("Skip for now");
    fd = open("test/asm/bot_test.s", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    TEST_ASSERT_NOT_EQUAL_INT(-1, fd);
    ft_putstr_fd("tir:	sti	r1,%:tirb,%1\n\tld	%123 ,r10\n\tld	%1   ,  r1,\n\n\n \t  tirb:\n\n\n\tld	%0,r11\n\n\n\ntirb:	live	%1\n", fd);
    lseek(fd, 0, SEEK_SET);
    bot = (t_bot *)ft_memalloc(sizeof(t_bot));
    TEST_ASSERT_NOT_NULL(bot);
    TEST_ASSERT_EQUAL_INT(KO, get_exec_code(bot, fd));
    close(fd);
    remove("test/asm/bot_test.s");
}
