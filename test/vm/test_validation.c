#include "unity.h"

#include "validation.h"

TEST_FILE("bot_processing.c")
TEST_FILE("init_arena.c")

void setUp(void)
{
}

void tearDown(void)
{
}

void test_valid_two_players(void)
{
    t_vm		*vm;
	const int	argc = 2;
	char	*argv[argc] = {
		"/Users/aimelda/Desktop/Corewar/resources/vm_champs/champs/championships/2014/bguy/sam_2.0.cor",
		"/Users/aimelda/Desktop/Corewar/resources/vm_champs/champs/championships/2014/bjacob/doge.cor"
	};

	vm = (t_vm*)ft_memalloc(sizeof(t_vm));
	vm->dump = -1;
	ft_printf("GOOD\n");
    TEST_ASSERT_EQUAL_INT(OK, validation(vm, argc, argv));
    // TEST_ASSERT_EQUAL_INT(2, (int)(((t_process*)vm->processes->content)->registries[0][0]));
	// TEST_ASSERT_EQUAL_INT(1, (int)(((t_process*)vm->processes->next->content)->registries[0][0]));
    // TEST_ASSERT_EQUAL_INT8_ARRAY(vm->players[0]->exec_code, vm->arena, vm->players[0]->exec_code_size);
	// for (int i = vm->players[0]->exec_code_size; i < delta; i++)
	// 	TEST_ASSERT_EACH_EQUAL_INT8('\x00', vm->arena + vm->players[0]->exec_code_size, delta - vm->players[0]->exec_code_size);
	// TEST_ASSERT_EQUAL_INT8_ARRAY(vm->players[1]->exec_code, vm->arena + delta, vm->players[1]->exec_code_size);
	// for (int i = delta + vm->players[1]->exec_code_size; i < MEM_SIZE; i++)
	// 	TEST_ASSERT_EACH_EQUAL_INT8('\x00', vm->arena + delta + vm->players[1]->exec_code_size, delta - vm->players[1]->exec_code_size);
}
