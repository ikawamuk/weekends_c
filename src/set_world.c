#include "define.h"
#include "hit_table_list.h"
#include "cylinder.h"
#include "plane.h"
#include "sphere.h"
#include "lambertian.h"
#include "light.h"
#include "world.h"

t_world	set_world(void)
{
	// color
	t_color black = construct_color(0, 0, 0);
	t_color gray = construct_color(0.1, 0.1, 0.1);
	t_color white = construct_color(0.73, 0.73, 0.73);
	t_color red = construct_color(0.65, 0.05, 0.05);
	t_color green = construct_color(0.12, 0.45, 0.15);
	t_vec3	bright = construct_vec(1, 1, 1);

	// world
	t_world	world;

	world.back_ground = black;
	world.objects = construct_htl();

	// wall
	t_plane	*wall_front = gen_plane(construct_vec(0, 0, -15), construct_vec(0, 0, 1), gen_lambertian(white));
	t_plane	*wall_left = gen_plane(construct_vec(6, 0, 0), construct_vec(-1, 0, 0), gen_lambertian(red));
	t_plane	*wall_right = gen_plane(construct_vec(-6, 0, 0), construct_vec(1, 0, 0), gen_lambertian(green));
	t_plane	*wall_back = gen_plane(construct_vec(0, 0, 1), construct_vec(0, 0, -1), gen_lambertian(gray));

	// floor
	t_plane	*floor = gen_plane(construct_vec(0, 0, 0), construct_vec(0, 1, 0), gen_lambertian(white));

	// ceiling
	t_plane	*ceiling = gen_plane(construct_vec(0, 10, 0), construct_vec(0, -1, 0), gen_lambertian(white));

	// objects
	t_sphere	*sphereA = gen_sphere(construct_vec(2, 1, -7), 1, gen_lambertian(construct_color(0.2, 0.2, 0.6)));
	t_sphere	*sphereB = gen_sphere(construct_vec(-3, 2, -13), 2, gen_lambertian(construct_color(0.5, 0.1, 0.1)));

	// light
	t_sphere	*light = gen_sphere(construct_vec(0, 9, -10), 1, gen_light(bright));

	add_htl(&world.objects, wall_front);
	add_htl(&world.objects, wall_left);
	add_htl(&world.objects, wall_right);
	add_htl(&world.objects, wall_back);
	add_htl(&world.objects, floor);
	add_htl(&world.objects, ceiling);
	add_htl(&world.objects, light);
	add_htl(&world.objects, sphereA);
	add_htl(&world.objects, sphereB);


	world.light_p = (t_hit_table *)light;
	return (world);
}
