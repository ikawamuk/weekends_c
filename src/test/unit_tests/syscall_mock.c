#include "syscall_mock.h"

int	_wrap_errno_ = 0;
enum e_error_syscall	err_syscall = NOTHING;
t_list	dummy_head = {0};

void *__wrap_malloc(size_t size)
{
	static int	called_count = 0;
	called_count++;
	if (err_syscall == MALLOC && called_count == 3)
	{
		errno = _wrap_errno_;
		return (NULL);
	}
	void	*p = __real_malloc(size);
	t_list	*new_node =  __real_malloc(sizeof(*new_node));
	new_node->content = p;
	new_node->next = NULL;
	t_list	*tail = &dummy_head;
	while (tail->next)
		tail = tail->next;
	tail->next = new_node;
	return (p);
}

void __wrap_free(void *ptr)
{
	bool	found = false;
	t_list	*cur = dummy_head.next;
	t_list	*prev = &dummy_head;
	while (cur)
	{
		if (cur->content == ptr)
		{
			found = true;
			prev->next = cur->next;
			__real_free(cur);
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
	if (!found)
	{
		fprintf(stderr, "ERROR: invalid free\n");
		abort();
	}
	return (__real_free(ptr));
}

bool	is_memory_leaked(void)
{
	return (dummy_head.next != NULL);
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
