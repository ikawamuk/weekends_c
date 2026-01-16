#include "cone.h"
#include "hit_node.h"
#include "rt_utils.h"

static void	get_cone_uv(const t_cone *self, t_hit_record *rec, t_vec3 cp)
{
	static const int	unit_height = 5;
	t_vec3	onb[3];
	build_onb(onb, self->direct);
	double	theta = atan2(dot(cp, onb[0]), dot(cp, onb[1]));
	double	height = dot(cp, self->direct);
	rec->u = 1.0 - (theta / (2.0 * M_PI) + 0.5);
	rec->v = fmod(height, unit_height) / unit_height;
	return ;
}

static void	assign_cone_hitrec(const t_cone *self, const t_ray ray, t_hit_record *rec, double solution)
{
	rec->t = solution;
	rec->p = at_ray(ray, rec->t);
	t_vec3	cp = sub_vec(rec->p, self->center);
	rec->normal = sub_vec(cp, \
		scal_mul_vec(self->direct, \
		dot(cp, self->direct) / pow2(cos(self->half_angle))));
	rec->ray_in = ray;
	rec->mat_ptr = self->hit_table.mat_ptr;
	rec->texture_p = self->hit_table.texture_p;
	get_cone_uv(self, rec, cp);
	return ;
}

bool	hit_cone(const void *s, const t_ray ray, t_hit_record *rec, t_range range)
{
	const t_cone	*self = s;
	t_vec3			co = sub_vec(ray.origin, self->center);
	double			d_v_dot = dot(ray.direct, self->direct);
	double			cos_pow2 = pow2(cos(self->half_angle));
	double			a = pow2(d_v_dot) \
							- dot(ray.direct, ray.direct) * cos_pow2;
	double			co_v_dot = dot(co, self->direct);
	double			b = d_v_dot * co_v_dot - dot(ray.direct, co) * cos_pow2;
	double			c = pow2(co_v_dot) - dot(co, co) * cos_pow2;
	double			discriminant = pow2(b) - a * c;

	if (discriminant < 0)
		return (false);
	double			root = sqrt(discriminant);
	double			solution = (-b + root) / a;
	if (check_range(solution, range))
	{
		assign_cone_hitrec(self, ray, rec, solution);
		return (true);
	}
	solution = (-b - root) / a;
	if (check_range(solution, range))
	{
		assign_cone_hitrec(self, ray, rec, solution);
		return (true);
	}
	return (false);
}

t_cone	construct_cone(t_point3 _center, t_vec3 _direct, double _half_angle, void *mat_ptr, void *texture_p)
{
	t_cone	cone;

	cone.hit_table.hit = hit_cone;
	cone.hit_table.clear = clear_primitive;
	cone.hit_table.mat_ptr = mat_ptr;
	cone.hit_table.texture_p = texture_p;
	cone.hit_table.have_aabb = false;
	cone.direct = _direct;
	cone.half_angle = _half_angle;
	cone.center = _center;
	return (cone);
}

t_cone	*gen_cone(t_point3 _center, t_vec3 _direct, double _half_angle, void *mat_ptr, void *texture_p)
{
	t_cone	*s;

	s = ft_calloc(1, sizeof(t_cone));
	if (!s)
		return (NULL);
	*s = construct_cone(_center, _direct, _half_angle, mat_ptr, texture_p);
	return (s);
}