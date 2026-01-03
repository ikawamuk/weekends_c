#include <assert.h>
#include <stdio.h>
#include "libft.h"
#include "syscall_mock.h"

int	validate(t_list *line_lst);

static t_list	*create_line_list(char **str_arr);
static int		normal_case();
static int		test_invalid_file_content();

int	test_validate_ambient();

int	test_validate()
{
	// alarm(10);
	err_syscall = NOTHING;
	fprintf(stdout, "\ntest_validate\n");
	normal_case();
	test_invalid_file_content();
	test_validate_ambient();
	// alarm(0);
	return (0);
}

static int	normal_case()
{
	fprintf(stdout, "--- normal case ---\n");
	char *line_arr[] = {
		"A 0.2 255,255,255\n",
		"C -50.0,0,20 0,0,1 70\n",
		"L -40.0,50.0,0.0 0.6 10,0,255\n",
		"sp 0.0,0.0,20.6 12.6 10,0,255\n",
		NULL
	};
	t_list *list = create_line_list(line_arr);
	assert(validate(list) == EXIT_SUCCESS);
	ft_lstclear(&list, free);
	assert(!is_memory_leaked());
	return (0);
}

static int	no_ambient()
{
	char *line_arr[] = {
		"C -50.0,0,20 0,0,1 70\n",
		"L -40.0,50.0,0.0 0.6 10,0,255\n",
		"sp 0.0,0.0,20.6 12.6 10,0,255\n",
		NULL
	};
	t_list *list = create_line_list(line_arr);
	assert(validate(list) == EXIT_FAILURE);
	ft_lstclear(&list, free);
	assert(!is_memory_leaked());
	return (0);
}

static int	more_ambient()
{
	fprintf(stdout, "--- normal case ---\n");
	char *line_arr[] = {
		"A 0.2 255,255,0\n",
		"A 0.8 0,255,255\n",
		"C -50.0,0,20 0,0,1 70\n",
		"L -40.0,50.0,0.0 0.6 10,0,255\n",
		"sp 0.0,0.0,20.6 12.6 10,0,255\n",
		NULL
	};
	t_list *list = create_line_list(line_arr);
	assert(validate(list) == EXIT_FAILURE);
	ft_lstclear(&list, free);
	assert(!is_memory_leaked());
	return (0);
}

static int	no_camera()
{
	char *line_arr[] = {
		"A 0.2 255,255,255\n",
		"L -40.0,50.0,0.0 0.6 10,0,255\n",
		"sp 0.0,0.0,20.6 12.6 10,0,255\n",
		NULL
	};
	t_list *list = create_line_list(line_arr);
	assert(validate(list) == EXIT_FAILURE);
	ft_lstclear(&list, free);
	assert(!is_memory_leaked());
	return (0);
}

static int	more_camera()
{
	fprintf(stdout, "--- normal case ---\n");
	char *line_arr[] = {
		"A 0.2 255,255,0\n",
		"C -50.0,0,20 0,0,1 70\n",
		"C 0.0,-200,10 0,0,1 100\n",
		"L -40.0,50.0,0.0 0.6 10,0,255\n",
		"sp 0.0,0.0,20.6 12.6 10,0,255\n",
		NULL
	};
	t_list *list = create_line_list(line_arr);
	assert(validate(list) == EXIT_FAILURE);
	ft_lstclear(&list, free);
	assert(!is_memory_leaked());
	return (0);
}

static int	invalid_identifer()
{
	char *line_arr[] = {
		"A 0.2 255,255,255\n",
		"C -50.0,0,20 0,0,1 70\n",
		"L -40.0,50.0,0.0 0.6 10,0,255\n",
		"sp 0.0,0.0,20.6 12.6 10,0,255\n",
		"er 0.0,0.0,20.6 12.6 10,0,255\n",
		NULL
	};
	t_list *list = create_line_list(line_arr);
	assert(validate(list) == EXIT_FAILURE);
	ft_lstclear(&list, free);
	assert(!is_memory_leaked());
	return (0);
}

static int	test_invalid_file_content()
{
	fprintf(stdout, "--- error case ---\n");
	no_ambient();
	more_ambient();
	no_camera();
	more_camera();
	invalid_identifer();
	return (0);
}

static t_list	*create_line_list(char **str_arr)
{
	t_list	*list = NULL;

	for (int i = 0; str_arr[i]; i++)
	{
		printf("str arr[i]: %s", str_arr[i]);
		ft_lstadd_back(&list, ft_lstnew(ft_strdup(str_arr[i])));
		printf("list head: %s", (char *)list->content);
	}
	return (list);
}
