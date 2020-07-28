#include "unity.h"
#include "corewar.h"
#include "print_byte_code.h"

TEST_FILE("check_extension.c")
TEST_FILE("create_and_open_file_cor.c")
TEST_FILE("get_magic_header.c")
TEST_FILE("init_bot.c")
TEST_FILE("ft_strcat.c")

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
