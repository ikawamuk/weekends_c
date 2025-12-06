#include "sphere.h"

void	assign_sphere_hitrec(t_hit_record *rec, double solution, const t_ray ray, t_sphere *self)
{
	rec->t = solution;
	rec->p = at_ray(ray, rec->t);
	rec->normal = scal_div_vec(sub_vec(rec->p, self->center), self->radius);
	rec->mat_ptr = self->mat_ptr;
	return ;
}

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
		if (0.001 < solution)
		{
			assign_sphere_hitrec(rec, solution, ray, self);
			return (true);
		}
		solution = (-half_b + root) / a;
		if (0.001 < solution)
		{
			assign_sphere_hitrec(rec, solution, ray, self);
			return (true);
		}
	}
	rec->t = 0;
	rec->p = construct_vec(0, 0, 0);
	rec->normal = construct_vec(0, 0, 0);
	rec->mat_ptr = 0;
	return (false);
}

t_sphere	construct_sphere(const t_point3 cen, const double r, t_material *mat_ptr)
{
	t_sphere	sphere;

	sphere.hit_table.hit = hit_sphere;
	sphere.center = cen;
	sphere.radius = r;
	sphere.hit_table.mat_ptr = mat_ptr;
	return (sphere);
}

t_sphere	*gen_sphere(const t_point3 cen, const double r, t_material *mat_ptr)
{
	t_sphere	*s = malloc(sizeof(*s));
	if (!s)
		return (NULL);
	*s = construct_sphere(cen, r, mat_ptr);
	return (s);
}