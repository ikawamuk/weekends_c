#include <stdio.h>
#include <assert.h>
#include <linux/limits.h>
#include <string.h>
#include "world.h"


static int	test_check_file_name();


int	set_world(t_world *world, const char *rt_file);
int	test_set_world()
{
	test_check_file_name();
	return (0);
}

int	read_rt(t_list **line_lst, const char *rt_file);
static int	test_ead_rt()
{
	{
		// normal case
		assert(EXIT_SUCCESS);
	}
	{
		// error case
		assert(EXIT_FAILURE);
	}
	return (0);
}


int	check_file_name(const char *rt_file);
static int	test_check_file_name()
{
	{
		// --- normal case ---
		assert(check_file_name("test.rt") == EXIT_SUCCESS);
		// assert(check_file_name("a.rt") == EXIT_SUCCESS);
		// assert(check_file_name(" .rt") == EXIT_SUCCESS);
		assert(check_file_name("テスト.rt") == EXIT_SUCCESS);
		assert(check_file_name("a..rt") == EXIT_SUCCESS);
		assert(check_file_name("a.txt.rt") == EXIT_SUCCESS);
		char long_name[NAME_MAX + 1];
		memset(long_name, 'a', NAME_MAX - 3);
		strcpy(long_name + (NAME_MAX - 3), ".rt");
		assert(check_file_name(long_name) == EXIT_SUCCESS);
	}
	{
		// --- error case ---
		assert(check_file_name("test.txt") == EXIT_FAILURE);
		assert(check_file_name("a.r") == EXIT_FAILURE);
		assert(check_file_name("a.") == EXIT_FAILURE);
		assert(check_file_name("a") == EXIT_FAILURE);
		assert(check_file_name("") == EXIT_FAILURE);
		assert(check_file_name("rt") == EXIT_FAILURE);
		assert(check_file_name(".rt") == EXIT_FAILURE);
		assert(check_file_name("a.rt ") == EXIT_FAILURE);
		assert(check_file_name("a.rt\n") == EXIT_FAILURE);
		// assert(check_file_name(".a.rt") == EXIT_FAILURE);
		assert(check_file_name("..rt") == EXIT_FAILURE);
		assert(check_file_name("\a.rt") == EXIT_FAILURE);
		assert(check_file_name("\n.rt") == EXIT_FAILURE);
		assert(check_file_name("a.rT") == EXIT_FAILURE);
		char too_long_name[NAME_MAX + 2];
		memset(too_long_name, 'a', NAME_MAX - 2);
		strcpy(too_long_name + (NAME_MAX - 2), ".rt");
		// assert(check_file_name(too_long_name) == EXIT_FAILURE);
	}
	return (0);
}
