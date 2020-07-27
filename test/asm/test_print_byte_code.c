#include "unity.h"
#include "corewar.h"
#include "print_byte_code.h"

TEST_FILE("check_extension.c")
TEST_FILE("create_and_open_file_cor.c")

void setUp(void)
{
}

void tearDown(void)
{
}

void test_print_byte_code_valid(void)
{
  TEST_ASSERT_EQUAL_INT(OK, print_byte_code("test.s", NULL));
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
