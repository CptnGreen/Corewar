#include "unity.h"

#include "get_name.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_batman_first_bytes(void)
{
    TEST_ASSERT_EQUAL_MEMORY("\x42\x61\x74\x6d\x61\x6e", get_name("Batman"), 6);
}
