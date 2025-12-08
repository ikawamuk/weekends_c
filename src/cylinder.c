#include "define.h"
#include "cylinder.h"
#include <stdlib.h> // malloc

void	set_cylinder_hitrec(t_hit_record *rec, const t_cylinder *self, const t_ray ray)
{
	t_vec3		w;
	double		h;
	t_point3	m;

	rec->ray_in = ray;
	rec->p = at_ray(ray, rec->t);
	rec->mat_ptr = self->hit_table.mat_ptr;

	w = sub_vec(rec->p, self->center);
	h = dot(w, self->direct); // 底面から衝突点までの高さを計算
	m = add_vec(self->center, scal_mul_vec(self->direct, h)); // 衝突店から軸上へ下ろされた垂線と軸の交点
	rec->normal = normalize(sub_vec(rec->p, m));
}

void	set_variables(const t_cylinder *self, const t_ray *ray, t_vec3 *abc)
{
	t_vec3	oc = sub_vec(ray->origin, self->center);
	t_vec3	d_d = cross(ray->direct, self->direct);
	t_vec3	oc_d = cross(oc, self->direct);

	abc->x = dot(d_d, d_d);
	abc->y = dot(d_d, oc_d);
	abc->z = dot(oc_d, oc_d) - self->radius * self->radius; 
}

bool	hit_cylinder(const void *s, const t_ray ray, t_hit_record *rec)
{
	const t_cylinder	*self = (t_cylinder *)s;
	t_vec3				abc;
	double				discriminant;
	double				root;
	double				solution;

	set_variables(self, &ray, &abc);
	discriminant = abc.y * abc.y - abc.x * abc.z;
	if (discriminant < 0)
		return (false);
	root = sqrt(discriminant);
	solution = (-abc.y - root) / abc.x;
	if (HIT_T_MIN < solution)
	{
		rec->t = solution;
		set_cylinder_hitrec(rec, self, ray);
		return (true);
	}
	solution = (-abc.y + root) / abc.x;
	if (HIT_T_MIN < solution)
	{
		rec->t = solution;
		set_cylinder_hitrec(rec, self, ray);
		return (true);
	}
	return (false);
}

t_cylinder	construct_cylinder(const t_point3 _center, const t_vec3 _direct, const double r, const double h, void *mat_ptr)
{
	t_cylinder	cylinder;

	cylinder.center = _center;
	cylinder.height = h;
	cylinder.direct = _direct;
	cylinder.radius = r;
	cylinder.hit_table.mat_ptr = mat_ptr;
	cylinder.hit_table.hit = hit_cylinder;
	return (cylinder);
}

t_cylinder	*gen_cylinder(const t_point3 _center, const t_vec3 _direct, const double r, const double h, void *mat_ptr)
{
	t_cylinder	*s = malloc(sizeof(t_cylinder));

	if (!s)
		return (NULL);
	*s = construct_cylinder(_center, _direct, r, h, mat_ptr);
	return (s);
}
