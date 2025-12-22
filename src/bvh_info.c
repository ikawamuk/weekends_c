#include "bvh_info.h"
#include "aabb.h"
#include "sphere.h"
#include "cylinder.h"
#include "lambertian.h"
#include "material.h"
#include "color.h"
#include "vec3.h"
#include "range.h"
#include "light.h"
#include "rt_utils.h"
#include "libft.h"
#include <stddef.h>

static t_hit_table	*get_object(char *line);
static t_sphere		*get_sphere_data(char *line);
t_sphere			*get_light_data(char *line);
static t_cylinder	*get_cylinder_data(char *line);

/*
@brief .rtファイルの一行からhit_table情報を作成する関数
*/
t_bvh_info	construct_bvh_info(char *line)
{
	t_bvh_info	info;
	t_range		zero_range;
	t_aabb		tmp_box;

	ft_bzero(&info, sizeof(t_aabb));
	ft_bzero(&zero_range, sizeof(t_range));
	info.data =	get_object(line);
	info.have_aabb = info.data->bounding_box(info.data, zero_range, &tmp_box);
	if (info.have_aabb == false)
		return (info);
	info.aabb = tmp_box;
	// 重心は比較にしか使われないので0.5はかけない
	info.centroid = add_vec(tmp_box.min, tmp_box.max);
	return (info);
}

static void	swap_info(t_bvh_info *a, t_bvh_info *b)
{
	t_bvh_info	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
@brief t_bvh_infoをクイックソート
*/
void	sort_bvh_info(t_bvh_info *info, int start, int end, bool (*comparator)(const t_bvh_info *, const t_bvh_info *))
{
	int			left;
	int			right;
	t_bvh_info	*pivot;

	if (end <= start)
		return ;
	if (start + 1 == end)
	{
		if (comparator(&info[end], &info[start]))
			swap_info(&info[start], &info[end]);
		return ;
	}
	left = start;
	right = (end - 1);
	pivot = &info[end];
	while (left < right)
	{
		while (left < end && comparator(&info[left], pivot))
			left++;
		while (start < right && comparator(pivot, &info[right]))
			right--;
		if (right <= left)
			break ;	
		swap_info(&info[left++], &info[right--]);
	}
	swap_info(&info[left], pivot);
	sort_bvh_info(info, start, left - 1, comparator);
	sort_bvh_info(info, left + 1, end, comparator);
}

static t_hit_table	*get_object(char *line)
{
	if (ft_strncmp("sp", line, 2) == 0)
		return ((t_hit_table *)get_sphere_data(line + 2));
	if (ft_strncmp("cy", line, 2) == 0)
		return ((t_hit_table *)get_cylinder_data(line + 2));
	if (*line == 'L')
		return ((t_hit_table *)get_light_data(line + 1));
	return (NULL);
}

static t_sphere	*get_sphere_data(char *line)
{
	t_point3	point;
	t_color		color;
	double		radius;
	t_material	*mat_ptr;

	skip_spaces(&line);
	point = get_vec(&line);
	skip_spaces(&line);
	radius = ft_strtod(line, &line) * 0.5;
	skip_spaces(&line);
	color = get_vec(&line);
	color = construct_color(color.x, color.y, color.z);
	mat_ptr = (t_material *)gen_lambertian(color);
	return (gen_sphere(point, radius, mat_ptr));
}

t_sphere	*get_light_data(char *line)
{
	t_point3	point;
	t_color		color;
	double		brightness_ratio;
	t_material	*mat_ptr;

	skip_spaces(&line);
	point = get_vec(&line);
	skip_spaces(&line);
	brightness_ratio = ft_strtod(line, &line);
	skip_spaces(&line);
	color = get_vec(&line);
	color = construct_color(color.x, color.y, color.z);
	color = scal_mul_vec(color, brightness_ratio);
	mat_ptr = (t_material *)gen_light(color);
	return (gen_sphere(point, LIGHT_RADIUS, mat_ptr));
}

static t_cylinder	*get_cylinder_data(char *line)
{
	t_point3	center;
	t_vec3		direct;
	t_color		color;
	double		height;
	double		radius;
	t_material	*mat_ptr;

	skip_spaces(&line);
	center = get_vec(&line);
	skip_spaces(&line);
	direct = get_vec(&line);
	skip_spaces(&line);
	height = ft_strtod(line, &line);
	skip_spaces(&line);
	radius = ft_strtod(line, &line) * 0.5; // 入力はdiameter
	skip_spaces(&line);
	color = get_vec(&line);
	color = construct_color(color.x, color.y, color.z);
	mat_ptr = (t_material *)gen_lambertian(color);
	return (gen_cylinder(center, direct, radius, height, mat_ptr));
}
