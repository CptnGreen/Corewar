#include "unity.h"

#include "chars_to_bytes.h"

void setUp(void)
{
}

void tearDown(void)
{
}

/*
** remove TEST_IGNORE() macro to activate this test
*/

void test_batman_first_bytes(void)
{
    TEST_IGNORE();
    TEST_ASSERT_EQUAL_MEMORY("\x42\x61\x74\x6d\x61\x6e", chars_to_bytes("Batman"), 6);
}
