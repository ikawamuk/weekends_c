#include "sphere.h"
#include "define.h"
#include "rt_utils.h"

static double	pdf_value_sphere(void *self, t_point3 p, t_vec3 direction);
static t_vec3	random_sphere(void *self, t_point3 p);

#include <stdio.h>
void	assign_sphere_hitrec(const t_sphere *self, t_hit_record *rec, double solution, const t_ray ray)
{
	rec->ray_in = ray;
	rec->t = solution;
	rec->p = at_ray(ray, rec->t); // 交点
	rec->normal = normalize(scal_div_vec(sub_vec(rec->p, self->center), self->radius)); // 面の向き
	rec->mat_ptr = self->hit_table.mat_ptr; // 材質
	get_sphere_uv(scal_div_vec(sub_vec(rec->p, self->center), self->radius), &rec->u, &rec->v);
	return ;
}

bool	hit_sphere(const void *s, const t_ray ray, t_hit_record *rec)
{
	const t_sphere	*self = s;
	t_vec3	oc = sub_vec(ray.origin, self->center);
	double	a = length_squared_vec(ray.direct);
	double	half_b = dot(oc, ray.direct);
	double	c = dot(oc, oc) - self->radius * self->radius;
	double	discriminant = half_b * half_b -  a * c;
	// printf("in hit_sphere\n");
	if (discriminant > 0)
	{
		double	root = sqrt(discriminant);
		double	solution = (-half_b - root)/a;
		if (HIT_T_MIN < solution) // 本家ではt_min, t_maxで縛り、特定区間内のレイだけ調べるがほとんどレイの始点からinfinityだったので、ここでは省略している。
		{
			assign_sphere_hitrec(self, rec, solution, ray);
			return (true);
		}
		solution = (-half_b + root) / a;
		if (0.001 < solution)
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
	sphere.hit_table.pdf_value = pdf_value_sphere;
	sphere.hit_table.random = random_sphere;
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

static double	pdf_value_sphere(void *s, t_point3 p, t_vec3 direction)
{
	t_sphere	*self = s;

	t_hit_record	rec;
	if (!self->hit_table.hit(self, construct_ray(p, direction), &rec))
		return (0);
	double	cos_theta_max = sqrt(1 - self->radius * self->radius / length_squared_vec(sub_vec(self->center, p)));
	double	solid_angle = 2 * M_PI * (1 - cos_theta_max);
	return (1 / solid_angle);
}

static t_vec3	random_to_sphere(double radius, double distance_squared)
{
	t_vec3	result;
	double	u1 = random_double(0, 1);
	double	u2 = random_double(0, 1);
	double	phi = 2 * M_PI * u1;
	double	cos_theta_max = sqrt(1 - radius * radius / distance_squared);

	result.z = 1 + u2 * (cos_theta_max - 1);
	result.x = cos(phi) * sqrt(1 - result.z * result.z);
	result.y = sin(phi) * sqrt(1 - result.z * result.z);
	return (result);
}

static t_vec3	random_sphere(void *s, t_point3 p)
{
	t_sphere	*self = s;

	t_vec3	direction = sub_vec(self->center, p);
	double	distance_squared = length_squared_vec(direction);
	t_vec3	onb[3];
	build_onb(onb, direction);
	return (local_onb(onb, random_to_sphere(self->radius, distance_squared)));
}