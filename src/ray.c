#include "ray.h"
#include "camera.h"
#include "define.h"

t_ray	construct_ray(t_point3 ori, t_vec3 dir)
{
	t_ray	ray;

	ray.origin = ori;
	ray.direct = dir;
	return (ray);
}

t_point3	at_ray(const t_ray ray, double t)
{
	return (add_vec(ray.origin, scal_mul_vec(ray.direct, t)));
}

t_ray	get_ray(t_camera camera, double u, double v)
{
	t_ray	ray;
	t_vec3	rd = scal_mul_vec(random_in_unit_disk(), LENS_RADIUS);
	t_vec3	offset = add_vec(scal_mul_vec(camera.onb[0], rd.x), scal_mul_vec(camera.onb[1], rd.y));
	t_vec3	ray_direct = sub_vec(add_vec(camera.higher_left_corner, scal_mul_vec(camera.horizontal, u)), \
						add_vec(scal_mul_vec(camera.vertical, v), camera.origin)); 
						// {higher_left_corner + u*horizontal}  -  {v*vertical + origin};

	ray = construct_ray(add_vec(camera.origin, offset), sub_vec(ray_direct, offset));
	
	return (ray);
}