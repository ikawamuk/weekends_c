#include "define.h"
#include "cylinder.h"
#include <stdlib.h> // malloc

bool	check_and_set_cylinder_hitrecord(t_hit_record *rec, const t_cylinder *self, const t_ray ray, double t)
{
	t_point3	_p;
	t_vec3		w;
	double		h;
	t_point3	m;

	_p = at_ray(ray, t);
	w = sub_vec(_p, self->center);
	h = dot(w, self->direct);
	if (h < 0 || self->height < h)
		return (false);
	rec->ray_in = ray;
	rec->p = _p;
	rec->mat_ptr = self->hit_table.mat_ptr;

	w = sub_vec(rec->p, self->center);
	h = dot(w, self->direct); // 底面から衝突点までの高さを計算
	m = add_vec(self->center, scal_mul_vec(self->direct, h)); // 衝突店から軸上へ下ろされた垂線と軸の交点
	rec->normal = normalize(sub_vec(rec->p, m));
	return (true);
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

bool	check_cap(const t_cylinder *self, const t_ray ray, t_point3 cap_center, t_vec3 cap_normal, double *t_cap)
{
	double	denom;
	double	t;
	t_point3	p;
	t_vec3		v;
	double		dist_squared;

	denom = dot(ray.direct, cap_normal);
	if (fabs(denom) < FLT_EPSILON)
		return (false);
	t = dot(sub_vec(cap_center, ray.origin), cap_normal) / denom;
	// (C - o) N / d N
	if (t < HIT_T_MIN)
		return (false);
	p = at_ray(ray, t);
	v = sub_vec(p, cap_center);
	dist_squared = length_squared_vec(v);
	if (dist_squared <= self->radius * self->radius)
	{
		*t_cap = t;
		return (true);
	}
	return (false);
}

bool	hit_cylinder(const void *s, const t_ray ray, t_hit_record *rec)
{
	const t_cylinder	*self = (t_cylinder *)s;
	t_vec3				abc;
	double				discriminant;
	double				root;
	double				solution;
	bool				hit_anything = false;
 	double				closest_t = INFINITY;

	set_variables(self, &ray, &abc);	
	discriminant = abc.y * abc.y - abc.x * abc.z;
	if (discriminant > 0)
	{
		root = sqrt(discriminant);
		solution = (-abc.y - root) / abc.x;
		if (HIT_T_MIN < solution)
		{
			if (check_and_set_cylinder_hitrecord(rec, self, ray, solution))
			{
				hit_anything = true;
				closest_t = solution;
			}
		}
		if (!hit_anything)
		{
			solution = (-abc.y + root) / abc.x;
			if (HIT_T_MIN < solution)
			{
				if (check_and_set_cylinder_hitrecord(rec, self, ray, solution))
				{
					hit_anything = true;
					closest_t = solution;
				}
			}
		}
	}
	double	t_cap;
	t_vec3	cap_normal = negative_vec(self->direct);
	if (check_cap(self, ray, self->center, cap_normal, &t_cap))
	{
		if (t_cap < closest_t)
		{
			rec->t = t_cap;
			rec->ray_in = ray;
			rec->p = at_ray(ray, t_cap);
			rec->normal = cap_normal;
			rec->mat_ptr = self->hit_table.mat_ptr;
			hit_anything = true;
			closest_t = t_cap;
		}
	}
	t_point3	top_center = add_vec(self->center, scal_mul_vec(self->direct, self->height));
	if (check_cap(self, ray, top_center, self->direct, &t_cap))
	{
		if (t_cap < closest_t)
		{
			rec->t = t_cap;
			rec->ray_in = ray;
			rec->p = at_ray(ray, t_cap);
			rec->normal = self->direct;
			rec->mat_ptr = self->hit_table.mat_ptr;
			hit_anything = true;
		}
	}
	return (hit_anything);
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
