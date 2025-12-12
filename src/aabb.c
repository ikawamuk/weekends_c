#include "aabb.h"
#include "ray.h"
#include <stdlib.h>

static void	rt_swap(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

// invDで割り算する回数を少なくする
// aabbはあたった点を記録する必要はないので、t_hit_recは引数に持たない
bool	hit_aabb(const void *s, const t_ray ray, t_t_range t_range)
{
	const t_aabb	*self = (const t_aabb *)s;

	// t0から入ってt1に向かって抜けていくイメージ
	for (int a = 0; a < 3; a++)
	{
		double	invD = 1.0f / axis_vec(ray.direct, a);
		double	t0 = (axis_vec(self->min, a) - axis_vec(ray.origin, a)) * invD;
		double	t1 = (axis_vec(self->max, a) - axis_vec(ray.origin, a)) * invD;
		if (invD < 0.0f)
			rt_swap(&t0, &t1);
		if (t_range.min < t0) // 各軸に入った中で最も遅いものを選択する
			t_range.min = t0;
		if (t1 < t_range.max) // 各軸に入った中で最も速いものを選択する
			t_range.max = t1;
		if (t_range.max <= t_range.min)
			return (false);
	}
	return (true);
}

t_aabb	construct_aabb(const t_point3 _min, const t_point3 _max)
{
	t_aabb	aabb;

	// 直方体の対局にある点同士のペア
	aabb.min = _min;
	aabb.max = _max;
	aabb.hit = hit_aabb;
	return (aabb);
}

// 質感mat_ptrはいらないと判断
t_aabb	*gen_aabb(const t_point3 _min, const t_point3 _max)
{
	t_aabb	*s;

	s = calloc(1, sizeof(t_aabb));
	if (!s)
		return (NULL);
	*s = construct_aabb(_min, _max);
	return (s);
}
