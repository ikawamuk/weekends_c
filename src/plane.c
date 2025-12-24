#include "plane.h"
#include "define.h"
#include <stdlib.h>
#include "rt_utils.h"

static void	get_plane_uv(t_point3 offset, t_vec3 normal, double *u, double *v);

bool	hit_plane(const void *s, const t_ray ray, t_hit_record *rec)
{
	const t_plane	*self = s;
	t_vec3			co = sub_vec(self->point, ray.origin);
	double			a = dot(co, self->normal);
	double			b = dot(ray.direct, self->normal);
	// b = 0はレイと平面が並行
	if (fabs(b) < FLT_EPSILON)
		return (false);
	double			solution = a / b;
	if (solution <= HIT_T_MIN)
		return (false);
	rec->ray_in = ray;
	rec->t = solution;
	rec->p = at_ray(ray, rec->t);
	rec->normal = normalize(self->normal); // オブジェクトの法線の向きは固定
	rec->mat_ptr = self->hit_table.mat_ptr;
	get_plane_uv(sub_vec(rec->p, self->point), rec->normal, &rec->u, &rec->v);
	return (true);
}

t_plane	construct_plane(const t_point3 p, const t_vec3 _normal, void *mat_ptr)
{
	t_plane	plane;

	plane.hit_table.hit = hit_plane;
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

/*
@param offset 交点 - 平面の基準点
2param normal 平面の法線ベクトル
*/
static void	get_plane_uv(t_point3 offset, t_vec3 normal, double *u, double *v)
{
	t_vec3	onb[3];
	static const int unit_edge = 10; // 単位平面の辺の長さ。大きいとタイルもでかい。unit_edge / N がタイルの一辺。

	build_onb(onb, normal);
	*u = dot(offset, onb[0]) / unit_edge; // unit_edgeのグリッドでみたu成分
	*v = dot(offset, onb[1]) / unit_edge; // unit_edgeのグリッドでみたv成分
	*u = *u - floor(*u); // グリッド内の位置
	*v = *v - floor(*v);
	return ;
}
