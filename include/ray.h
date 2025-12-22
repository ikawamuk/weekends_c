#ifndef RAY_H
# define RAY_H

#include "vec3.h"
#include "camera.h"
#include "ray.h"

typedef struct ray
{
	t_point3	origin;
	t_vec3		direct;
}	t_ray;

t_ray		construct_ray(t_point3 ori, t_vec3 dir);
t_point3	at_ray(const t_ray ray, double t);
t_ray		get_ray(t_camera camera, double u, double v);

#endif
