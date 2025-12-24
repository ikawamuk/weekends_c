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


#include <stdio.h>
t_world	set_world(void)
{
	// color
	t_color black = construct_color(0, 0, 0);
	t_color white = construct_color(200,200,200);
	t_color red = construct_color(170, 13, 13);
	t_color green = construct_color(40, 240, 40);
	t_vec3	bright = construct_vec(50, 50, 50);

	// world
	t_world	world;

	world.back_ground = black;
	world.objects = construct_htl();
	world.lights = construct_light_list();

	// wall
	t_plane	*wall_front = gen_plane(construct_vec(0, 0, -15), construct_vec(0, 0, 1), gen_lambertian(gen_solid_texture(white)));
	t_plane	*wall_left = gen_plane(construct_vec(6, 0, 0), construct_vec(-1, 0, 0), gen_lambertian(gen_solid_texture(red)));
	// t_plane	*wall_right = gen_plane(construct_vec(-6, 0, 0), construct_vec(1, 0, 0), gen_lambertian(gen_solid_texture(green)));

	// floor
	t_plane	*floor = gen_plane(construct_vec(0, 0, 0), construct_vec(0, 1, 0), gen_lambertian( \
		gen_checker_texture(gen_solid_texture(construct_color(240, 240, 240)), gen_solid_texture(green))));

	// ceiling
	// t_plane	*ceiling = gen_plane(construct_vec(0, 10, 0), construct_vec(0, -1, 0), gen_lambertian(white));

	// objects
	t_sphere	*sphereA = gen_sphere(construct_vec(2, 1, -7), 1, gen_lambertian(gen_solid_texture(construct_color(51, 51, 150))));
	t_sphere	*sphereB = gen_sphere(construct_vec(0, 2, -13), 2, gen_metal(construct_color(254, 254, 254), 0.01));
	// t_sphere	*sphereC = gen_sphere(construct_vec(-2, 1, -5), 1, gen_dielectric(1.5));
	// t_sphere	*sphereD = gen_sphere(construct_vec(1.5, 0.5, -5), -0.5, gen_dielectric(1.5));
	t_sphere	*sphereE = gen_sphere(construct_vec(-3, 4, -7), 2, \
	gen_lambertian(\
		gen_checker_texture(\
			gen_solid_texture(construct_color(76, 76, 240)), \
			gen_solid_texture(construct_color(180, 51, 51)))));

	// light
	t_sphere	*lightA = gen_sphere(construct_vec(-4, 9, -10), 0.5, gen_light(bright));
	t_sphere	*lightB = gen_sphere(construct_vec(0, 9, 10), 5, gen_light(construct_vec(10, 10, 10)));

	add_htl(&world.objects, wall_front);
	add_htl(&world.objects, wall_left);
	// add_htl(&world.objects, wall_right);
	// add_htl(&world.objects, wall_back);
	add_htl(&world.objects, floor);
	// add_htl(&world.objects, ceiling);
	add_htl(&world.objects, lightA);
	add_htl(&world.objects, lightB);
	add_htl(&world.objects, sphereA);
	add_htl(&world.objects, sphereB);
	// add_htl(&world.objects, sphereC);
	// add_htl(&world.objects, sphereD);
	add_htl(&world.objects, sphereE);

	add_htl(&world.lights, lightA);
	add_htl(&world.lights, lightB);
	return (world);
}
