#include <stdlib.h>
#include "lambertian.h"
#include "rt_utils.h"

t_lambertian	construct_lambertian(t_color alb)
{
	t_lambertian	lam;

	lam.material.scatter = scatter_lambertian;
	lam.material.emitted = emitted_non_light;
	lam.albedo = construct_color(alb.x, alb.y, alb.z);
	return (lam);
}

bool	scatter_lambertian(void *s, t_hit_record rec, t_color *attenuation, t_ray *scattered)
{
	t_lambertian	*self = s;
	t_vec3	scatter_direction = add_vec(rec.normal , random_unit_vector());
	if (dot(rec.normal, rec.ray_in.direct) > 0)
		scatter_direction = negative_vec(scatter_direction);
	*scattered = construct_ray(rec.p, scatter_direction);
	*attenuation = self->albedo;
	return (true);
}

t_lambertian	*gen_lambertian(t_color alb)
{
	t_lambertian	*p = malloc(sizeof(*p));
	if (!p)
		return (NULL);
	*p = construct_lambertian(alb);
	return (p);
}
