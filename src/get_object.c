#include "aabb.h"
#include "sphere.h"
#include "cylinder.h"
#include "lambertian.h"
#include "material.h"
#include "color.h"
#include "vec3.h"
#include "range.h"
#include "light.h"
#include "plane.h"
#include "cone.h"
#include "metal.h"
#include "dielectric.h"
#include "rt_utils.h"
#include "libft.h"
#include <stddef.h>

static t_sphere		*get_sphere_data(char *line);
t_sphere			*get_light_data(char *line);
static t_cylinder	*get_cylinder_data(char *line);
static t_plane		*get_plane_data(char *line);
static t_cone 		*get_cone_data(char *line);

/*
@brief 文字列からプリミティブの情報を取得する関数
*/
t_hit_table	*get_object(char *line)
{
	if (ft_strncmp("sp", line, 2) == 0)
		return ((t_hit_table *)get_sphere_data(line + 2));
	if (ft_strncmp("cy", line, 2) == 0)
		return ((t_hit_table *)get_cylinder_data(line + 2));
	if (ft_strncmp("pl", line, 2) == 0)
		return ((t_hit_table *)get_plane_data(line + 2));
	if (ft_strncmp("co", line, 2) == 0)
		return ((t_hit_table *)get_cone_data(line + 2));
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
	// mat_ptr = (t_material *)gen_lambertian(gen_bump_texture(color));
	mat_ptr = (t_material *)gen_lambertian(gen_solid_texture(color));
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
	radius = ft_strtod(line, &line) * 0.5; // 入力はdiameter
	skip_spaces(&line);
	height = ft_strtod(line, &line);
	skip_spaces(&line);
	color = get_vec(&line);
	color = construct_color(color.x, color.y, color.z);
	mat_ptr = (t_material *)gen_lambertian(gen_checker_texture(gen_solid_texture(constant_vec(0.2)), gen_solid_texture(color)));
	return (gen_cylinder(center, direct, radius, height, mat_ptr));
}

static t_plane	*get_plane_data(char *line)
{
	t_point3	point;
	t_vec3		direct;
	t_color		color;
	t_material	*mat_ptr;

	skip_spaces(&line);
	point = get_vec(&line);
	skip_spaces(&line);
	direct = get_vec(&line);
	skip_spaces(&line);
	color = get_vec(&line);
	color = construct_color(color.x, color.y, color.z);
	mat_ptr = (t_material *)gen_lambertian(\
		gen_checker_texture(\
			gen_solid_texture(color), \
			gen_solid_texture(constant_vec(1.0))));
	return (gen_plane(point, direct, mat_ptr));
}

static t_cone *get_cone_data(char *line)
{
	t_point3	point;
	t_vec3		direct;
	double		half_angle;
	t_color		color;
	t_material	*mat_ptr;

	skip_spaces(&line);
	point = get_vec(&line);
	skip_spaces(&line);
	direct = get_vec(&line);
	skip_spaces(&line);
	half_angle = to_radians(ft_strtod(line, &line));
	skip_spaces(&line);
	color = get_vec(&line);
	color = construct_color(color.x, color.y, color.z);
	// mat_ptr = (t_material *)gen_lambertian(gen_solid_texture(color));
	mat_ptr = (t_material *)gen_lambertian(gen_checker_texture(gen_solid_texture(construct_vec(1.0,1.0,1.0)), gen_solid_texture(color)));
	return (gen_cone(point, direct, half_angle, mat_ptr));
}
