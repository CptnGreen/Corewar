#include "unity.h"

#include "get_zeroes.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_three_zeroes(void)
{
    TEST_ASSERT_EQUAL_MEMORY("\x00\x00\x00", get_zeroes(3), 3);
}
