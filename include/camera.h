#ifndef CAMERA_H
# define CAMERA_H

#include "vec3.h"
#include "ray.h"
#include "libft.h"

typedef struct s_camera
{
	t_point3	origin;
	t_point3	higher_left_corner;
	t_vec3		horizontal;
	t_vec3		vertical;
}	t_camera;

t_camera	set_camera(t_list *line_lst);
t_camera	construct_camera(const t_point3 _origin, const t_vec3 _orient, double vfov);
t_ray		get_ray(t_camera camera, double u, double v);

#endif
