#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"

int	_wrap_open_errno_ = 0;

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
		t_list	*line_list;
		fprintf(stderr, "--- normal case ---\n");
		_wrap_open_errno_ = 0;
		assert(read_rt(&line_list, file_name) == EXIT_SUCCESS);
	}
	{
		t_list	*line_list;
		fprintf(stderr, "--- error case ---\n");
		_wrap_open_errno_ = ENOENT;
		assert(read_rt(&line_list, file_name) == EXIT_FAILURE);
	}
	fclose(fp);
	alarm(0);
	return (0);
}

int __real_open(const char *pathname, int flags);

int	__wrap_open(const char *pathname, int flags)
{
	if (_wrap_open_errno_)
	{
		errno = _wrap_open_errno_;
		return (-1);
	}
	return (__real_open(pathname, flags));
}