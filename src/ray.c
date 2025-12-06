#include "ray.h"

t_ray	construct_ray(const t_point3 ori, const t_vec3 dir)
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
