#include "camera.h"
#include "define.h"

t_camera	construct_camera(void)
{
	t_camera	camera;
	double		focal_length = 1.0;
	double		screen_height = 2.0;
	double		screen_width = screen_height * ASPECT_RATIO;

	camera.origin = construct_vec(0, 0, 0);
	camera.horizontal = construct_vec(screen_width, 0, 0);
	camera.vertical = construct_vec(0, screen_height, 0);
	camera.higher_left_corner = add_vec(sub_vec(camera.origin, scal_div_vec(camera.horizontal, 2)), sub_vec(scal_div_vec(camera.vertical, 2), construct_vec(0, 0, focal_length)));
	// higher_left_corner = {origin - horizontal/2 } +  {vertical/2 - vec3(0, 0, focal_length)} ;
	return (camera);
}

t_ray	get_ray(t_camera camera, double u, double v)
{
	t_ray	ray;

	ray = construct_ray(camera.origin, 
		sub_vec(add_vec(camera.higher_left_corner, scal_mul_vec(camera.horizontal, u)), sub_vec(scal_mul_vec(camera.vertical, v), camera.origin)));
	// {higher_left_corner + u*horizontal}  -  {v*vertical - origin};
	return (ray);
}
