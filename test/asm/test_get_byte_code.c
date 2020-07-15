#include "unity.h"

#include "get_byte_code.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_brazhnik(void)
{
	char	*asm_code;

	asm_code = \
		".name       \"Batman\"\n\
.comment    \"This city needs me\"\n\
\n\
loop:\n\
		sti r1, %:live, %1\n\
live:\n\
		live %0\n\
		ld %0, r2\n\
		zjmp %:loop";

	TEST_ASSERT_EQUAL_STRING(asm_code, asm_code);
}
