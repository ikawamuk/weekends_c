#include "aabb.h"
#include "ray.h"
#include <stdlib.h>

// while文中でベクトルの要素を取るために作成した関数。
static double	get_xyz(t_point3 p, int i)
{
	if (i == 0)
		return (p.x);
	if (i == 1)
		return (p.y);
	return (p.z); 
}

static void	rt_swap(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

// invDで割り算する回数を少なくする
bool	hit_aabb(const void *s, const t_ray ray, t_hit_record *rec, t_t_range *t_range)
{
	const t_aabb	*self = (const t_aabb *)s;
	t_t_range		temp_range = *t_range;

	for (int a = 0; a < 3; a++)
	{
		double	invD = get_xyz(ray.direct, a);
		double	t0 = (get_xyz(self->min, a) - get_xyz(ray.origin, a)) * invD;
		double	t1 = (get_xyz(self->max, a) - get_xyz(ray.origin, a)) * invD;
		if (invD < 0.0f)
			rt_swap(&t0, &t1);
		if (temp_range.min < t0) // 各軸に入った中で最も遅いものを選択する
			temp_range.min = t0;
		if (t0 < temp_range.max) // 各軸に入った中で最も速いものを選択する
			temp_range.max = t1;
		if (temp_range.max <= temp_range.min)
			return (false);
	}
	return (true);
}

t_aabb	construct_aabb(const t_point3 _min, const t_point3 _max)
{
	t_aabb	aabb;

	aabb.min = _min;
	aabb.max = _max;
	aabb.hit_table.hit = hit_aabb;
	aabb.hit_table.mat_ptr = NULL;
}

// 質感mat_ptrはいらないと判断
t_aabb	*gen_aabb(const t_point3 _min, const t_point3 _max)
{
	t_aabb	*s;

	s = calloc(1, sizeof(t_aabb));
	if (!s)
		return (NULL);
	return (s);
}
