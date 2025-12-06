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
		// rec.mat_ptr->sctter()で反射レイを計算。
		t_point3 target	= add_vec(rec.p, add_vec(rec.normal, random_unit_vector())); // rec.p + rec.normal + random_unit_vect()
		return (mul_vec(ray_color(construct_ray(rec.p, sub_vec(target, rec.p)), world, depth - 1), 0.5)); // ray_color() * 0.5;
	}
	t_vec3	unit_direction = normalize(ray.direct);
	double	t = 0.5 * (unit_direction.y + 1.0);
	return (add_vec(mul_vec(construct_vec(1.0, 1.0, 1.0), (1.0 - t)), mul_vec(construct_vec(0.5, 0.7, 1.0), t)));
}
