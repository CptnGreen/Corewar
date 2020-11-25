#include "unity.h"

#include "init_arena.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_valid_two_players(void)
{
	t_vm		*vm;
	const int	num_players = 2;
	const int	delta = MEM_SIZE / num_players;

	vm = (t_vm*)ft_memalloc(sizeof(t_vm));
	for (int i = 0; i < num_players; i++)
		vm->players[i] = (t_bot*)ft_memalloc(sizeof(t_bot));
	vm->players[0]->exec_code_size = 22;
	vm->players[1]->exec_code_size = 33;
	ft_memcpy(vm->players[0]->exec_code, "\x0b\x68\x01\x00\x07\x00\x01\x01\x00\x00\x00\x00\x02\x90\x00\x00\x00\x00\x02\x09\xff\xed", vm->players[0]->exec_code_size);
	ft_memcpy(vm->players[1]->exec_code, "\x0b\x68\x01\x00\x1c\x00\x01\x02\x90\x00\x00\x00\x7b\x0a\x02\x90\x00\x00\x00\x01\x01\x02\x90\x00\x00\x00\x00\x0b\x01\x00\x00\x00\x01", vm->players[1]->exec_code_size);
    TEST_ASSERT_EQUAL_INT(OK, init_arena(vm, num_players));
    TEST_ASSERT_EQUAL_INT(2, (int)(((t_process*)vm->processes->content)->registries[0][0]));
	TEST_ASSERT_EQUAL_INT(1, (int)(((t_process*)vm->processes->next->content)->registries[0][0]));
    TEST_ASSERT_EQUAL_INT8_ARRAY(vm->players[0]->exec_code, vm->arena, vm->players[0]->exec_code_size);
	for (int i = vm->players[0]->exec_code_size; i < delta; i++)
		TEST_ASSERT_EACH_EQUAL_INT8('\x00', vm->arena + vm->players[0]->exec_code_size, delta - vm->players[0]->exec_code_size);
	TEST_ASSERT_EQUAL_INT8_ARRAY(vm->players[1]->exec_code, vm->arena + delta, vm->players[1]->exec_code_size);
	for (int i = delta + vm->players[1]->exec_code_size; i < MEM_SIZE; i++)
		TEST_ASSERT_EACH_EQUAL_INT8('\x00', vm->arena + delta + vm->players[1]->exec_code_size, delta - vm->players[1]->exec_code_size);
}
