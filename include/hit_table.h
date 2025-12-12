#ifndef HIT_TABLE_H
# define HIT_TABLE_H

#include <stdbool.h>
#include "vec3.h"
#include "ray.h"
#include "t_range.h"
#include "aabb.h"

typedef struct s_material t_material;

typedef struct s_hit_record
{
	t_ray		ray_in;
	t_point3	p;
	t_vec3		normal;
	t_material	*mat_ptr;
	double		t;
}	t_hit_record;

typedef struct s_hit_table t_hit_table;

/*
@param bounding_box そのオブジェクトがaabbを構築できたか?
					無限の平面はaabbを構築できない。
*/
struct s_hit_table
{
	bool		(*hit)(const void *self, const t_ray ray, t_hit_record *rec, t_t_range t_range);
	bool		(*bounding_box)(const void *self, t_aabb *output_box); // 本物は時間を引数に持つが、この実装は時間軸を持たないため、省略
	t_material	*mat_ptr;
};

#endif
