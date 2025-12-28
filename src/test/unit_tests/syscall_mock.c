#include "syscall_mock.h"

int	_wrap_errno_ = 0;
enum e_error_syscall	err_syscall = NOTHING;

void *__wrap_malloc(size_t size)
{
	if (err_syscall == MALLOC)
	{
		errno = _wrap_errno_;
		return (NULL);
	}
	return (__real_malloc(size));
}

ssize_t	__wrap_read(int fd, void *buf, size_t count)
{
	if (err_syscall == READ)
	{
		errno = _wrap_errno_;
		return (-1);
	}
	return (__real_read(fd, buf, count));
}

int	__wrap_open(const char *pathname, int flags)
{
	if (err_syscall == OPEN)
	{
		errno = _wrap_errno_;
		return (-1);
	}
	return (__real_open(pathname, flags));
}
