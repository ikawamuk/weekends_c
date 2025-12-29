#include "hit_table.h"
#include "material.h"
#include "world.h"
#include "ray.h"
#include "define.h"
#include "color.h"
#include "rt_utils.h"
#include "libft.h"

static t_color	diffuse_specular_color(t_hit_record hrec, const t_world *world);

t_color	phong_color(t_ray ray, const t_world *world)
{
	t_hit_record	hrec;
	t_range			range;
	t_color			color;
	t_scatter_record	srec;

	range = construct_range(HIT_T_MIN, INFINITY);
	if (world->node == NULL || world->node->hit(world->node, ray, &hrec, range) == false)
		return (world->back_ground);
	ft_bzero(&color, sizeof(t_color));
	hrec.mat_ptr->scatter(hrec.mat_ptr, &hrec, &srec);
	color = add_vec(color, scal_mul_vec(scal_mul_vec(srec.attenuation, world->ambient_ratio), 0.3)); // 環境光の影響を追加
	color = add_vec(color, scal_mul_vec(mul_vec(diffuse_specular_color(hrec, world), srec.attenuation), 0.7));
	return (color);
}

static bool	is_in_shadow(const t_world *world, t_point3 p, t_vec3 light_dir, double light_dis)
{
	t_ray			to_light;
	t_hit_record	tmp_rec;
	t_range			range;

	to_light = construct_ray(p, light_dir);
	range = construct_range(HIT_T_MIN, light_dis);
	return (world->node->hit(world->node, to_light, &tmp_rec, range));
}

t_color	calc_specular(t_hit_record hrec, t_vec3 light_dir)
{
	// ヒットポイントにおいて光線が完全に反射される方向
	t_vec3	reflect_vec = add_vec(scal_mul_vec(hrec.normal, \
		2 * dot(light_dir, hrec.normal)), negative_vec(light_dir));
	t_vec3	point_to_camera = normalize(negative_vec(hrec.ray_in.direct));
	return (constant_vec(10 * pow(fmax(0, dot(reflect_vec, point_to_camera)), 15 /*小さいほど広範囲がテカる*/)));
}

static t_color	diffuse_specular_color(t_hit_record hrec, const t_world *world)
{
	t_color				diffuse;
	t_color				specular;
	t_hit_table_node	*curr_light;
	t_vec3				light_dir; // 反射面から光源への方向ベクトル
	double				light_dis;

	ft_bzero(&diffuse, sizeof(t_color));
	ft_bzero(&specular, sizeof(t_color));
	curr_light = world->lights.head;
	while (curr_light)
	{
		light_dir = sub_vec(curr_light->data->aabb.centroid, hrec.p);
		light_dis = length_vec(light_dir);
		light_dir = normalize(light_dir);
		if (is_in_shadow(world, hrec.p, light_dir, light_dis) == false)
		{
			t_color	light_color = scal_mul_vec(curr_light->data->mat_ptr->emitted(curr_light->data->mat_ptr, hrec), 0.01);
			diffuse = add_vec(diffuse, mul_vec(constant_vec(fmax(0, dot(light_dir, hrec.normal))), light_color));
			specular = add_vec(specular, mul_vec(calc_specular(hrec, light_dir), light_color));
		}
		curr_light = curr_light->next;
	}
	return (add_vec(scal_mul_vec(diffuse, 0.5), scal_mul_vec(specular, 0.5)));
}
