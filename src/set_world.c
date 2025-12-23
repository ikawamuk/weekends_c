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
#include "texture.h"

t_world	set_world(void)
{
	// color
	t_color	black = construct_vec(0, 0, 0);
	t_color	white = construct_vec(0.9, 0.9, 0.9);
	t_color	gray = construct_vec(0.5, 0.5, 0.5);
	t_color	red = construct_vec(0.9, 0.2, 0.2);
	t_color	green = construct_vec(0.2, 0.9, 0.2);
	// t_color	blue = construct_vec(0.2, 0.2, 0.9);

	// wall
	t_plane		*wall = gen_plane(construct_vec(0, 0, -40), construct_vec(-1, 0, 2), gen_lambertian(gen_solid_texture(gray)));

	// floor
	t_plane		*floor = gen_plane(construct_vec(0, 0, 0), construct_vec(0, 1, 0), \
						gen_lambertian(gen_bump_texture(white)));

	// objects
	t_sphere	*shpereA = gen_sphere(construct_vec(-2.5, 2, -10), 2, gen_lambertian(gen_solid_texture(red)));
	t_sphere	*shpereB = gen_sphere(construct_vec(3, 4, -18), 4, gen_lambertian(gen_solid_texture(green)));

	// light
	t_sphere	*light = gen_sphere(construct_vec(0, 20, 5), 3, gen_light(construct_vec(50, 50, 50)));



	t_world		world = construct_world(black);

	add_htl(&world.objects, wall);
	add_htl(&world.objects, floor);
	add_htl(&world.objects, shpereA);
	add_htl(&world.objects, shpereB);
	add_htl(&world.objects, light);

	add_htl(&world.lights, light);
	return (world);
}
