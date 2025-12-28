#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "syscall_mock.h"

int	validate_ambient(char *line);

/*
	Ambient lighting:
	A 0.2 255,255,255
	∗ identifier: A
	∗ ambient lighting ratio in the range [0.0,1.0]: 0.2
	∗ R, G, B colors in the range [0-255]: 255, 255, 255
*/
int	test_validate_ambient()
{
	fprintf(stdout, "\ntest_validate_ambient\n");
	{
		fprintf(stdout, "--- normal case ---\n");
		// assert(validate_ambient("") == EXIT_SUCCESS && !is_memory_leaked());
	}
	{
		fprintf(stdout, "--- error case ---\n");
		assert(validate_ambient("") == EXIT_FAILURE && !is_memory_leaked());
	}
	return (0);
}


