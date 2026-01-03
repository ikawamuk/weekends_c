#include "triangle.h"
#include "define.h"
#include "rt_utils.h"

static void	get_triangle_uv(t_point3 offset, t_vec3 normal, double *u, double *v);

static bool	hit_triangle(const void *s, const t_ray ray, t_hit_record *rec, t_range range)
{
	const t_tri	*self = s;
	t_vec3		ao = sub_vec(self->vertex[0], ray.origin);
	double		a = dot(ao, self->normal);
	double		b = dot(ray.direct, self->normal);

	if (fabs(b) < FLT_EPSILON)
		return (false);
	double	solution = a / b;
	if (check_range(solution, range) == false)
		return (false);
	t_point3	point = at_ray(ray, solution);
	t_point3	ap = sub_vec(point, self->vertex[0]);
	t_point3	bp = sub_vec(point, self->vertex[1]);
	t_point3	cp = sub_vec(point, self->vertex[2]);
	if (dot(self->normal, cross(self->side[0], ap)) < 0 \
		|| dot(self->normal, cross(self->side[1], bp)) < 0 \
		|| dot(self->normal, cross(self->side[2], cp)) < 0)
		return (false);
	rec->mat_ptr = self->hit_table.mat_ptr;
	rec->normal = self->normal;
	rec->p = point;
	rec->ray_in = ray;
	rec->t = solution;
	get_triangle_uv(ap, self->normal, &rec->u, &rec->v);
	return (true);
}

static t_aabb	construct_triangle_aabb(t_tri triangle)
{
	t_point3	_min;
	t_point3	_max;

	_min = construct_vec(fmin(fmin(triangle.vertex[0].x, triangle.vertex[1].x), triangle.vertex[2].x), \
		fmin(fmin(triangle.vertex[0].y, triangle.vertex[1].y), triangle.vertex[2].y), \
		fmin(fmin(triangle.vertex[0].z, triangle.vertex[1].z), triangle.vertex[2].z));
	_max = construct_vec(fmax(fmax(triangle.vertex[0].x, triangle.vertex[1].x), triangle.vertex[2].x), \
		fmax(fmax(triangle.vertex[0].y, triangle.vertex[1].y), triangle.vertex[2].y), \
		fmax(fmax(triangle.vertex[0].z, triangle.vertex[1].z), triangle.vertex[2].z));
	return (construct_aabb(_min, _max));
}

t_tri	construct_triangle(t_point3 _a, t_point3 _b, t_point3 _c, void *mat_ptr)
{
	t_tri	triangle;

	triangle.vertex[0] = _a;
	triangle.vertex[1] = _b;
	triangle.vertex[2] = _c;
	triangle.side[0] = sub_vec(_b, _a);
	triangle.side[1] = sub_vec(_c, _b);
	triangle.side[2] = sub_vec(_a, _c);
	triangle.normal = normalize(cross(triangle.side[0], negative_vec(triangle.side[2])));
	triangle.hit_table.hit = hit_triangle;
	triangle.hit_table.clear = clear_primitive;
	triangle.hit_table.have_aabb = true;
	triangle.hit_table.aabb = construct_triangle_aabb(triangle);
	triangle.hit_table.mat_ptr = mat_ptr;
	return (triangle);
}

t_tri	*gen_triangle(t_point3 _a, t_point3 _b, t_point3 _c, void *mat_ptr)
{
	t_tri	*s = ft_calloc(1, sizeof(t_tri));

	if (!s)
		return (NULL);
	*s = construct_triangle(_a, _b, _c, mat_ptr);
	return (s);
}

/*
@param offset 交点 - 平面の基準点
2param normal 平面の法線ベクトル
*/
static void	get_triangle_uv(t_point3 offset, t_vec3 normal, double *u, double *v)
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
