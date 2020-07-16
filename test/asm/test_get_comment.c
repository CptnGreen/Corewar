#include "unity.h"

#include "get_comment.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_1(void)
{
    TEST_ASSERT_EQUAL_MEMORY("\x63\x6f\x6d\x6d\x65\x6e\x74", get_comment("comment"), 7);
}
void test_2()
{
    TEST_ASSERT_EQUAL_MEMORY("\x61",get_comment("a"),1);
}
