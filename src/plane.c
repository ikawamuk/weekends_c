#include "plane.h"
#include "define.h"
#include <stdlib.h>

bool	hit_plane(const void *s, const t_ray ray, t_hit_record *rec, t_t_range t_range)
{
	const t_plane	*self = s;
	t_vec3			co = sub_vec(self->point, ray.origin);
	double			a = dot(co, self->normal);
	double			b = dot(ray.direct, self->normal);
	// b = 0はレイと平面が並行
	if (fabs(b) < FLT_EPSILON)
		return (false);
	double			solution = a / b;
	if (check_range(solution, t_range) == false)
		return (false);
	rec->ray_in = ray;
	rec->t = solution;
	rec->p = at_ray(ray, rec->t);
	rec->normal = self->normal; // オブジェクトの法線の向きは固定
	rec->mat_ptr = self->hit_table.mat_ptr;
	return (true);
}

// bool	bounding_plane(const void *s, t_t_range t_range, t_aabb *output_box)
// {
// 	const t_plane	*self = (const t_plane *)s;
// 	t_vec3			edge_vec;

// 	// 法線ベクトルに垂直な単位ベクトル
// 	edge_vec = normalize(construct_vec(self->normal.y, -self->normal.x, 0));
// 	(void)t_range;
// 	// 平面に沿った薄い直方体
// 	*output_box = construct_aabb(sub_vec(sub_vec(self->point, \
// 								scal_mul_vec(edge_vec, 100.0f)), \
// 								self->normal), \
// 								add_vec(add_vec(self->point, \
// 								scal_mul_vec(edge_vec, -100.0f)), \
// 								self->normal));
// 	return (true);
// }

t_plane	construct_plane(const t_point3 p, const t_vec3 _normal, void *mat_ptr)
{
	t_plane	plane;

	plane.hit_table.hit = hit_plane;
	// plane.hit_table.bounding_box = bounding_plane;
	plane.hit_table.mat_ptr = mat_ptr;
	plane.point = p;
	plane.normal = _normal;
	return (plane);
}

t_plane	*gen_plane(const t_point3 p, const t_vec3 _normal, void *mat_ptr)
{
	t_plane	*s = malloc(sizeof(t_plane));

	if (!s)
		return (NULL);
	*s = construct_plane(p, _normal, mat_ptr);
	return (s);
}
