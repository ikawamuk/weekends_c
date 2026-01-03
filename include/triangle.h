#ifndef TRIANGLE_H
# define TRIANGLE_H

# include "vec3.h"
# include "hit_table.h"

/*
@param vertex 頂点A, B, C
@param side 辺ベクトル AB, BC, CA
*/
typedef struct s_tri
{
	t_hit_table	hit_table;
	t_vec3		normal;
	t_point3	vertex[3];
	t_point3	side[3];
}	t_tri;

t_tri	*gen_triangle(t_point3 _a, t_point3 _b, t_point3 _c, void *mat_ptr);

#endif