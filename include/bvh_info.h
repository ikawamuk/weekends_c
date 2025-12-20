#ifndef BVH_INFO_H
# define BVH_INFO_H

# include "hit_table.h"
# include "vec3.h"
# include "aabb.h"
# include <stddef.h>

/*
@brief bvhを構築するための準備構造体
@param centroid 重心,bvh比較用
@param have_aabb aabbを持っているか否か
*/
typedef struct s_bvh_info
{
	t_hit_table	*data;
	bool		have_aabb;
	t_point3	centroid;
	t_aabb		aabb;
}	t_bvh_info;

t_bvh_info	construct_bvh_info(char *line);
void		sort_bvh_info(t_bvh_info *info, int start, int end, bool (*comparator)(const t_bvh_info *, const t_bvh_info *));

#endif