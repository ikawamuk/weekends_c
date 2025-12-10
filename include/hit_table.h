#ifndef HIT_TABLE_H
# define HIT_TABLE_H

#include <stdbool.h>
#include "vec3.h"
#include "ray.h"
#include "t_range.h"

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

struct s_hit_table
{
	bool		(*hit)(const void *self, const t_ray ray, t_hit_record *rec, t_t_range *t_range);
	t_material	*mat_ptr;
};

#endif
