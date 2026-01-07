#include "bvh.h"
#include "camera.h"
#include "fcntl.h"
#include "define.h"
#include "hit_table_list.h"
#include "cylinder.h"
#include "plane.h"
#include "sphere.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "light.h"
#include "world.h"
#include "rt_utils.h"
#include "libft.h"
#include <stdio.h>

int				validate(t_list *line_lst);
int				set_light(t_hit_table_list *lights, t_list *line_lst);
int				set_object(t_hit_table **node, t_list *line_lst);
int		read_rt(t_list **line_lst, const char *rt_file);
int		check_file_name(const char *rt_file);
static void		err_file_name(void);
static void 	set_back_ground(t_world *world, t_list *line_lst);

/*
@param world uninitialized variable pointer
@param rt_file file name of .rt file: argv[1]
*/
int	set_world(t_world *world, const char *rt_file)
{
	t_list	*line_lst;

	if (check_file_name(rt_file))
		return (EXIT_FAILURE);
	if (read_rt(&line_lst, rt_file))
		return (ft_lstclear(&line_lst, free), EXIT_FAILURE);
	if (validate(line_lst))
		return (ft_lstclear(&line_lst, free), EXIT_FAILURE);
	ft_bzero(world, sizeof(t_world));
	world->camera = set_camera(line_lst);
	set_back_ground(world, line_lst);
	if (set_object(&world->node, line_lst))
		return (ft_lstclear(&line_lst, free), EXIT_FAILURE);
	if (set_light(&world->lights, line_lst))
		return (ft_lstclear(&line_lst, free), EXIT_FAILURE);
	ft_lstclear(&line_lst, free);
	return (EXIT_SUCCESS);
}

/*
@param line_list uninitialized variable pointer
@param .rt file that has valid name
*/
int	read_rt(t_list **line_lst, const char *rt_file)
{
	int		fd;
	int		gnl_ret;
	char	*line;
	t_list	head;
	t_list	*curr;

	fd = open(rt_file, O_RDONLY);
	if (fd == -1)
		return (perror("open"), EXIT_FAILURE);
	ft_bzero(&head, sizeof(t_list));
	curr = &head;
	while (curr)
	{
		gnl_ret = ft_get_next_line(fd, &line);
		if (gnl_ret == -1)
			return (perror("read"), EXIT_FAILURE);
		else if (gnl_ret == -2)
			return (perror("malloc"), EXIT_FAILURE);
		else if (gnl_ret == 0)
			break ;
		if (*line == '\n')
		{
			free(line);
			continue ;
		}
		curr->next = ft_lstnew(line);
		curr = curr->next;
	}
	if (!curr)
		return (perror("malloc"), EXIT_FAILURE);
	*line_lst = head.next;
	return (EXIT_SUCCESS);
}

int	check_file_name(const char *rt_file)
{
	size_t	rt_file_len;

	if (rt_file[0] == '.')
		return (err_file_name(), EXIT_FAILURE);
	rt_file_len = ft_strlen(rt_file);
	if (rt_file_len <= 3 || ft_strcmp(rt_file + rt_file_len - 3, ".rt"))
		return (err_file_name(), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	err_file_name(void)
{
	static char	*msg = "SET .rt FILE CORRECTLY.";

	ft_putendl_fd(msg, STDERR_FILENO);
}

/*
@brief 設定されていなかったらデフォルト値を呼び出す
*/
static void set_back_ground(t_world *world, t_list *line_lst)
{
	static char	*def = "0.8 100,200,255";
	char	*line;
	t_color	back_ground;

	line = get_word_line(line_lst, "A");
	if (!line)
		line = def;
	world->ambient_ratio = ft_strtod(line, &line);
	skip_spaces(&line);
	back_ground = get_vec(&line);
	world->back_ground = construct_color(back_ground.x, back_ground.y, back_ground.z);;
}

void	clear_world(t_world *world)
{
	clear_htl(world->lights);
	clear_bvh(world->node);
	world->node = NULL;
}

// #include "define.h"
// #include "hit_table_list.h"
// #include "cylinder.h"
// #include "plane.h"
// #include "sphere.h"
// #include "lambertian.h"
// #include "light.h"
// #include "world.h"
// t_world	set_world(void)
// {
// 	// color
// 	t_color black = construct_color(0, 0, 0);
// 	// t_color gray = construct_color(0.1, 0.1, 0.1);
// 	t_color white = construct_color(0.73, 0.73, 0.73);
// 	t_color red = construct_color(0.65, 0.05, 0.05);
// 	t_color green = construct_color(0.12, 0.45, 0.15);
// 	// t_vec3	bright = construct_vec(50, 50, 50);

// 	// world
// 	t_world	world;

// 	world.back_ground = black;
// 	world.objects = construct_htl();

// 	// wall
// 	t_plane	*wall_front = gen_plane(construct_vec(0, 0, -15), construct_vec(0, 0, 1), gen_lambertian(white));
// 	t_plane	*wall_left = gen_plane(construct_vec(6, 0, 0), construct_vec(-1, 0, 0), gen_lambertian(red));
// 	t_plane	*wall_right = gen_plane(construct_vec(-6, 0, 0), construct_vec(1, 0, 0), gen_lambertian(green));
// 	// t_plane	*wall_back = gen_plane(construct_vec(0, 0, 1), construct_vec(0, 0, -1), gen_lambertian(gray));

// 	// floor
// 	t_plane	*floor = gen_plane(construct_vec(0, 0, 0), construct_vec(0, 1, 0), gen_lambertian(white));

// 	// ceiling
// 	// t_plane	*ceiling = gen_plane(construct_vec(0, 10, 0), construct_vec(0, -1, 0), gen_lambertian(white));

// 	// objects
// 	t_sphere	*sphereA = gen_sphere(construct_vec(2, 1, -7), 1, gen_lambertian(construct_color(0.2, 0.2, 0.6)));
// 	t_sphere	*sphereB = gen_sphere(construct_vec(-3, 2, -13), 2, gen_lambertian(construct_color(0.5, 0.1, 0.1)));

// 	// light
// 	t_sphere	*lightA = gen_sphere(construct_vec(-4, 9, -10), 0.5, gen_light(construct_vec(100, 100, 100)));
// 	t_sphere	*lightB = gen_sphere(construct_vec(4, 9, -10), 0.5, gen_light(construct_vec(100, 100, 100)));

// 	add_htl(&world.objects, wall_front);
// 	add_htl(&world.objects, wall_left);
// 	add_htl(&world.objects, wall_right);
// 	// add_htl(&world.objects, wall_back);
// 	add_htl(&world.objects, floor);
// 	// add_htl(&world.objects, ceiling);
// 	add_htl(&world.objects, lightA);
// 	add_htl(&world.objects, lightB);
// 	add_htl(&world.objects, sphereA);
// 	add_htl(&world.objects, sphereB);


// 	world.lights = construct_light_list();
// 	add_htl(&world.lights, lightA);
// 	add_htl(&world.lights, lightB);
// 	return (world);
// }
