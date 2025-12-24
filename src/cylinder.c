#include "define.h"
#include "cylinder.h"
#include "range.h"
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
	rec->t = t;
	rec->ray_in = ray;
	rec->p = _p;
	rec->mat_ptr = self->hit_table.mat_ptr;

	m = add_vec(self->center, scal_mul_vec(self->direct, h)); // 衝突点から軸上へ下ろされた垂線と軸の交点
	rec->normal = scal_div_vec(sub_vec(rec->p, m), self->radius);
	return (true);
}

void	set_variables(const t_cylinder *self, const t_ray *ray, t_vec3 *abc)
{
	t_vec3	oc = sub_vec(ray->origin, self->center);

	double dot_dd = dot(ray->direct, ray->direct);
	double dot_da = dot(ray->direct, self->direct);
	double dot_ococ = dot(oc, oc);
	double dot_oca = dot(oc, self->direct);
	double dot_doc = dot(ray->direct, oc);

	abc->x = dot_dd - dot_da * dot_da;
	abc->y = dot_doc - dot_da * dot_oca;
	abc->z = dot_ococ - dot_oca * dot_oca - self->radius * self->radius;
}

bool	check_cap(const t_cylinder *self, const t_ray ray, t_point3 cap_center, t_vec3 cap_normal, double *t_cap)
{
	double		denom;
	double		t;
	t_point3	p;
	t_vec3		v;
	double		dist_squared;

	denom = dot(ray.direct, cap_normal);
	if (fabs(denom) < FLT_EPSILON)
		return (false);
	t = dot(sub_vec(cap_center, ray.origin), cap_normal) / denom;
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

bool	hit_cylinder(const void *s, const t_ray ray, t_hit_record *rec, t_range range)
{
	const t_cylinder	*self = (t_cylinder *)s;
	t_vec3				abc;
	double				discriminant;
	double				root;
	double				solution;
	bool				hit_anything = false;

	set_variables(self, &ray, &abc);	
	discriminant = abc.y * abc.y - abc.x * abc.z;
	if (discriminant > 0)
	{
		root = sqrt(discriminant);
		solution = (-abc.y - root) / abc.x;
		if (check_range(solution, range))
		{
			if (check_and_set_cylinder_hitrecord(rec, self, ray, solution))
			{
				hit_anything = true;
				range.max = solution;
			}
		}
		if (!hit_anything)
		{
			solution = (-abc.y + root) / abc.x;
			if (check_range(solution, range))
			{
				if (check_and_set_cylinder_hitrecord(rec, self, ray, solution))
				{
					hit_anything = true;
					range.max = solution;
				}
			}
		}
	}
	double	t_cap;
	t_vec3	cap_normal = negative_vec(self->direct);
	if (check_cap(self, ray, self->center, cap_normal, &t_cap))
	{
		if (check_range(t_cap, range))
		{
			rec->t = t_cap;
			rec->ray_in = ray;
			rec->p = at_ray(ray, t_cap);
			rec->normal = cap_normal;
			rec->mat_ptr = self->hit_table.mat_ptr;
			hit_anything = true;
			range.max = t_cap;
		}
	}
	t_point3	top_center = add_vec(self->center, scal_mul_vec(self->direct, self->height));
	if (check_cap(self, ray, top_center, self->direct, &t_cap))
	{
		if (check_range(t_cap, range))
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

static t_aabb	construct_cylinder_aabb(const t_cylinder *self)
{
	// それぞれの軸方向の広がり
	t_vec3		delta;
	// 円柱の天板中心座標
	t_point3	top_c;
	t_point3	_min;
	t_point3	_max;

	// r * √(1 - sinθ)
	// cosθ = direct.x
	// θはx軸と軸ベクトルのなす角
	delta.x = self->radius * sqrt(1 - self->direct.x * self->direct.x);
	delta.y = self->radius * sqrt(1 - self->direct.y * self->direct.y);
	delta.z = self->radius * sqrt(1 - self->direct.z * self->direct.z);
	top_c = add_vec(self->center, scal_mul_vec(self->direct, self->height));
	_min.x = fmin(self->center.x, top_c.x) - delta.x;
	_min.y = fmin(self->center.y, top_c.y) - delta.y;
	_min.z = fmin(self->center.z, top_c.z) - delta.z;
	_max.x = fmax(self->center.x, top_c.x) + delta.x;
	_max.y = fmax(self->center.y, top_c.y) + delta.y;
	_max.z = fmax(self->center.z, top_c.z) + delta.z;
	return (construct_aabb(_min, _max));
}

t_cylinder	construct_cylinder(const t_point3 _center, const t_vec3 _direct, const double r, const double h, void *mat_ptr)
{
	t_cylinder	cylinder;

	cylinder.center = _center;
	cylinder.height = h;
	cylinder.direct = normalize(_direct);
	cylinder.radius = r;
	cylinder.hit_table.mat_ptr = mat_ptr;
	cylinder.hit_table.hit = hit_cylinder;
	cylinder.hit_table.clear = clear_primitive;
	cylinder.hit_table.have_aabb = true;
	cylinder.hit_table.aabb = construct_cylinder_aabb(&cylinder);
	return (cylinder);
}

t_cylinder	*gen_cylinder(const t_point3 _center, const t_vec3 _direct, const double r, const double h, void *mat_ptr)
{
	t_cylinder	*s = ft_calloc(1, sizeof(t_cylinder));

	if (!s)
		return (NULL);
	*s = construct_cylinder(_center, _direct, r, h, mat_ptr);
	return (s);
}
