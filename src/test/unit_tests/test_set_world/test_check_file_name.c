#include <assert.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	check_file_name(const char *rt_file);
int	test_check_file_name()
{
	alarm(2);
	{
		fprintf(stderr, "--- normal case ---\n");
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
		fprintf(stderr, "--- error case ---\n");
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
	alarm(0);
	return (0);
}
