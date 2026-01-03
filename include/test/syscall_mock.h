#ifndef SYSCALL_MOCK_H
# define SYSCALL_MOCK_H

#include <errno.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include "libft.h"

enum e_error_syscall{
	NOTHING,
	OPEN,
	READ,
	WRITE,
	MALLOC
};

extern int _wrap_errno_;
extern enum e_error_syscall err_syscall;
extern t_list dummy_head;

void	*__real_malloc(size_t size);
void	*__wrap_malloc(size_t size);
void	__real_free(void *ptr);
void	__wrap_free(void *ptr);
bool	is_memory_leaked(void);
ssize_t	__real_read(int fd, void *buf, size_t count);
ssize_t	__wrap_read(int fd, void *buf, size_t count);
int	__real_open(const char *pathname, int flags);
int	__wrap_open(const char *pathname, int flags);

#endif
