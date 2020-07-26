#include "unity.h"
#include "corewar.h"
#include "print_byte_code.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_print_byte_code_NeedToImplement(void)
{
  TEST_ASSERT_EQUAL_INT(OK, print_byte_code("test.s", NULL));
  //TEST_IGNORE_MESSAGE("Need to Implement print_byte_code");
}
