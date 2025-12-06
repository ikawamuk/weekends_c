#include "sphere.h"

bool	hit_sphere(void *s, const t_ray ray, t_hit_record *rec)
{
	t_sphere	*self = s;
	t_vec3	oc = sub_vec(ray.origin, self->center);
	double	a = length_squared_vec(ray.direct);
	double	half_b = dot(oc, ray.direct);
	double	c = dot(oc, oc) - self->radius * self->radius;
	double	discriminant = half_b * half_b -  a * c;
	if (discriminant > 0)
	{
		double	root = sqrt(discriminant);
		double	solution = (-half_b - root)/a;
		if (0 < solution)
		{
			rec->t = solution;
			rec->p = at_ray(ray, rec->t);
			rec->normal = div_vec(sub_vec(rec->p, self->center), self->radius);
			return (true);
		}
	}
	rec->t = 0;
	rec->p = construct_vec(0, 0, 0);
	rec->normal = construct_vec(0, 0, 0);
	return (false);
}

t_sphere	construct_sphere(const t_point3 cen, const double r)
{
	t_sphere	sphere;

	sphere.hit_table.hit = hit_sphere;
	sphere.center = cen;
	sphere.radius = r;
	return (sphere);
}

t_sphere	*gen_sphere(const t_point3 cen, const double r)
{
	t_sphere			*s = malloc(sizeof(*s));
	if (!s)
		return (NULL);
	*s = construct_sphere(cen, r);
	return (s);
}