#include "sphere.h"
#include "define.h"

void	assign_sphere_hitrec(const t_sphere *self, t_hit_record *rec, double solution, const t_ray ray)
{
	rec->ray_in = ray;
	rec->t = solution;
	rec->p = at_ray(ray, rec->t); // 交点
	rec->normal = scal_div_vec(sub_vec(rec->p, self->center), self->radius); // 面の向き
	rec->mat_ptr = self->hit_table.mat_ptr; // 材質
	return ;
}

bool	hit_sphere(const void *s, const t_ray ray, t_hit_record *rec, t_t_range *t_range)
{
	const t_sphere	*self = s;
	t_vec3	oc = sub_vec(ray.origin, self->center);
	double	a = length_squared_vec(ray.direct);
	double	half_b = dot(oc, ray.direct);
	double	c = dot(oc, oc) - self->radius * self->radius;
	double	discriminant = half_b * half_b -  a * c;
	if (discriminant > 0)
	{
		double	root = sqrt(discriminant);
		double	solution = (-half_b - root)/a;
		if (check_range(solution, *t_range)) // 本家ではt_min, t_maxで縛り、特定区間内のレイだけ調べるがほとんどレイの始点からinfinityだったので、ここでは省略している。
		{
			assign_sphere_hitrec(self, rec, solution, ray);
			return (true);
		}
		// 以下の部分ほんとに必要？？？->レイの始点が球の内部のとき有効みたい（ex:カメラをガラス球の中に入れる。）
		solution = (-half_b + root) / a;
		if (check_range(solution, *t_range))
		{
			assign_sphere_hitrec(self, rec, solution, ray);
			return (true);
		}
	}
	return (false);
}

t_sphere	construct_sphere(const t_point3 cen, const double r, void *mat_ptr)
{
	t_sphere	sphere;

	sphere.hit_table.hit = hit_sphere;
	sphere.hit_table.mat_ptr = mat_ptr;
	sphere.center = cen;
	sphere.radius = r;
	return (sphere);
}

t_sphere	*gen_sphere(const t_point3 cen, const double r, void *mat_ptr)
{
	t_sphere	*s = malloc(sizeof(*s));
	if (!s)
		return (NULL);
	*s = construct_sphere(cen, r, mat_ptr);
	return (s);
}