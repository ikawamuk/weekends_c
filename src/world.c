#include "world.h"

t_world	construct_world(t_color back_ground)
{
	t_world	world;

	world.back_ground = back_ground;
	world.objects = construct_htl();
	world.lights = construct_light_list();
	return (world);
}
