#include <stdio.h>
int	test_check_file_name();
int	test_read_rt();
int	test_validate();

int	test_set_world()
{
	fprintf(stdout, "\ntest_set_world\n");
	test_check_file_name();
	// test_read_rt();
	test_validate();
	return (0);
}

