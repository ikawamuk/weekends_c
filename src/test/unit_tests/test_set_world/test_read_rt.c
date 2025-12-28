#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"
#include "syscall_mock.h"

int	read_rt(t_list **line_lst, const char *rt_file);
int	test_read_rt()
{
	alarm(3);

	const char *file_name ="test_read.rt";
	FILE *fp = fopen(file_name, "w");
	assert(fp);
	fprintf(fp, "A 0.2 255,255,255\n");
	fprintf(fp, "C -50.0,0,20 0,0,1 70\n");
	fprintf(fp, "L -40.0,50.0,0.0 0.6 10,0,255\n");
	fprintf(fp, "sp 0.0,0.0,20.6 12.6 10,0,255\n");
	// fclose(fp);
	{
		_wrap_errno_ = 0;
		err_syscall = NOTHING;
		t_list	*line_list;
		fprintf(stdout, "--- normal case ---\n");
		assert(read_rt(&line_list, file_name) == EXIT_SUCCESS);
	}
	{
		t_list	*line_list;
		fprintf(stdout, "--- error case ---\n");
		{
			err_syscall = OPEN;
			_wrap_errno_ = ENOENT;
			assert(read_rt(&line_list, file_name) == EXIT_FAILURE && !is_memory_leaked());
			_wrap_errno_ = EACCES;
			assert(read_rt(&line_list, file_name) == EXIT_FAILURE && !is_memory_leaked());
		}
		{
			err_syscall = READ;
			_wrap_errno_ = EBADF;
			assert(read_rt(&line_list, file_name) == EXIT_FAILURE && !is_memory_leaked());
			_wrap_errno_ = EISDIR;
			assert(read_rt(&line_list, file_name) == EXIT_FAILURE && !is_memory_leaked());
			_wrap_errno_ = EFAULT;
			assert(read_rt(&line_list, file_name) == EXIT_FAILURE && !is_memory_leaked());
			_wrap_errno_ = ENOMEM;
			assert(read_rt(&line_list, file_name) == EXIT_FAILURE && !is_memory_leaked());
		}
		{
			err_syscall = MALLOC;
			_wrap_errno_ = ENOMEM;
			assert(read_rt(&line_list, file_name) == EXIT_FAILURE);
		}
		_wrap_errno_ = 0;
		err_syscall = NOTHING;
	}
	fclose(fp);
	alarm(0);
	return (0);
}
