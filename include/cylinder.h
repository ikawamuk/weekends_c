#ifndef CYLINDER_H
# define CYLINDER_H

# include "hit_table.h"
# include "vec3.h"
/*
@brief シリンダー
@param center: 底面中心座標
@param orient: 軸の方向ベクトル
@param height: 高さ
@param ridus: 半径
*/
typedef struct s_cylinder
{
	t_hit_table	hit_table;
	t_point3	center;
	t_vec3		direct;
	double		height;
	double		radius;
}	t_cylinder;

t_cylinder	*gen_cylinder(const t_point3 _center, const t_vec3 _direct, const double r, const double h, void *mat_ptr, void *texture_p);

#endif