#include "unity.h"
#include "corewar.h"
#include "print_byte_code.h"

TEST_FILE("check_extension.c")
TEST_FILE("create_and_open_file_cor.c")
TEST_FILE("get_magic_header.c")
TEST_FILE("init_bot.c")
TEST_FILE("put_in_cor_magic_header_and_bot_name.c")
TEST_FILE("ft_putnbr_fd.c")
TEST_FILE("put_exec_code_size_in_cor.c")

void setUp(void)
{
}

void tearDown(void)
{
}

void test_print_byte_code_valid(void)
{
  t_bot   *bot;

  bot = init_bot();
  ft_strcat(bot->name, "Batman");
  bot->exec_code_size = 0;
  ft_strcat(bot->comment, "This city needs me");
  ft_strcat(bot->exec_code, "\x0b\x68");
  TEST_ASSERT_EQUAL_INT(OK, print_byte_code("test.s", bot));
}

void test_print_byte_code_invalid(void)
{
  TEST_ASSERT_EQUAL_INT(KO, print_byte_code("test.v", NULL));
  TEST_ASSERT_EQUAL_INT(KO, print_byte_code("test.", NULL));
  TEST_ASSERT_EQUAL_INT(KO, print_byte_code("test", NULL));
  TEST_ASSERT_EQUAL_INT(KO, print_byte_code("t.es.t", NULL));
  TEST_ASSERT_EQUAL_INT(KO, print_byte_code("te.s.st", NULL));
  TEST_ASSERT_EQUAL_INT(KO, print_byte_code("te.s.st.cor", NULL));
}

void test_print_byte_code_NeedToImplement_3(void)
{
}
