#ifndef HIT_TABLE_H
# define HIT_TABLE_H

#include <stdbool.h>
#include "vec3.h"
#include "ray.h"

typedef struct s_material t_material;

/*
@param ray_in 入射レイ
@param p　衝突点
@param normal 物体の法線ベクトル(入射レイに関わらず同じ向き)
@param mat_ptr 衝突点の材質
@param 入射レイの媒介変数
*/
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
	bool		(*hit)(const void *self, const t_ray ray, t_hit_record *rec);
	t_material	*mat_ptr;
};

#endif
