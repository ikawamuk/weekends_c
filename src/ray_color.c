#include "vec3.h"
#include "ray.h"
#include "hit_table_list.h"

t_color ray_color(const t_ray ray, t_hit_table_list *world, int depth)
{
	t_hit_record	rec;

	if (depth <= 0)
		return (construct_vec(0, 0, 0));
	if (world->hit_table.hit(world, ray, &rec))
	{
		// Next: ここの処理をrec.mat_ptr->sctter()で反射レイを計算する方法におきかえる。
		t_point3	target = add_vec(rec.p , add_vec(rec.normal , random_unit_vector()));
		t_ray		scattered = construct_ray(rec.p, sub_vec(target, rec.p));
		t_color		attenuation = construct_vec(0.5, 0.5, 0.5);
		return (mul_vec(attenuation, ray_color(scattered, world, depth - 1)));
		// return (0.5 * ray_color(ray(rec.p, target - rac.p), world, depth - 1));
	}
	t_vec3	unit_direction = normalize(ray.direct);
	double	t = 0.5 * (unit_direction.y + 1.0);
	return (add_vec(scal_mul_vec(construct_vec(1.0, 1.0, 1.0), (1.0 - t)), scal_mul_vec(construct_vec(0.5, 0.7, 1.0), t)));
}
