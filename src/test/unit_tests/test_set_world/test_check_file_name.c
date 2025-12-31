#include <assert.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "syscall_mock.h"

int	check_file_name(const char *rt_file);
int	test_check_file_name()
{
	fprintf(stdout, "\ntest_check_file_name\n");
	alarm(2);
	{
		fprintf(stdout, "--- normal case ---\n");
		assert(check_file_name("test.rt") == EXIT_SUCCESS && !is_memory_leaked());
		assert(check_file_name("a.rt") == EXIT_SUCCESS && !is_memory_leaked());
		assert(check_file_name(" .rt") == EXIT_SUCCESS && !is_memory_leaked());
		assert(check_file_name("テスト.rt") == EXIT_SUCCESS && !is_memory_leaked());
		assert(check_file_name("a..rt") == EXIT_SUCCESS);
		assert(check_file_name("a.txt.rt") == EXIT_SUCCESS && !is_memory_leaked());
		char long_name[NAME_MAX + 1];
		memset(long_name, 'a', NAME_MAX - 3);
		strcpy(long_name + (NAME_MAX - 3), ".rt");
		assert(check_file_name(long_name) == EXIT_SUCCESS && !is_memory_leaked());
	}
	{
		fprintf(stdout, "--- error case ---\n");
		assert(check_file_name("test.txt") == EXIT_FAILURE && !is_memory_leaked());
		assert(check_file_name("a.r") == EXIT_FAILURE && !is_memory_leaked());
		assert(check_file_name("a.") == EXIT_FAILURE && !is_memory_leaked());
		assert(check_file_name("a") == EXIT_FAILURE && !is_memory_leaked());
		assert(check_file_name("") == EXIT_FAILURE && !is_memory_leaked());
		assert(check_file_name("rt") == EXIT_FAILURE && !is_memory_leaked());
		assert(check_file_name(".rt") == EXIT_FAILURE && !is_memory_leaked());
		assert(check_file_name("a.rt ") == EXIT_FAILURE && !is_memory_leaked());
		assert(check_file_name("a.rt\n") == EXIT_FAILURE && !is_memory_leaked());
		assert(check_file_name(".a.rt") == EXIT_FAILURE && !is_memory_leaked());
		assert(check_file_name("..rt") == EXIT_FAILURE && !is_memory_leaked());
		assert(check_file_name("\a.rt") == EXIT_FAILURE && !is_memory_leaked());
		assert(check_file_name("\n.rt") == EXIT_FAILURE && !is_memory_leaked());
		assert(check_file_name("a.rT") == EXIT_FAILURE && !is_memory_leaked());
		char too_long_name[NAME_MAX + 2];
		memset(too_long_name, 'a', NAME_MAX - 2);
		strcpy(too_long_name + (NAME_MAX - 2), ".rt");
		assert(check_file_name(too_long_name) == EXIT_FAILURE && !is_memory_leaked());
	}
	alarm(0);
	return (0);
}
