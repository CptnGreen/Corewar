#include "unity.h"

#include "get_magic_header.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_func(void)
{
    TEST_ASSERT_EQUAL_MEMORY("\x00\xea\x83\xf3", get_magic_header(), 4);
}
