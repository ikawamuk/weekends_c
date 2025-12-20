#include "camera.h"
#include "define.h"
#include "vec3.h"
#include "rt_utils.h"
#include "libft.h"

static double	degrees_to_radians(const double degrees);

t_camera	set_camera(t_list *line_lst)
{
	static char	*def = "0,0,0 0,0,-1 80";
	char		*line;
	t_point3	origin;
	t_vec3		direct;
	double		vfov;

	line = get_word_line(line_lst, "C");
	if (!line)
		line = def;
	origin = get_vec(&line);
	skip_spaces(&line);
	direct = get_vec(&line);
	skip_spaces(&line);
	vfov = ft_strtod(line, &line);
	return (construct_camera(origin, direct, vfov));
}

/* 
@param _origin: カメラの座標
@param _orient: カメラの方向ベクトル
@param vfov: 垂直方向のfield of view
*/
t_camera	construct_camera(const t_point3 _origin, const t_vec3 _orient, double vfov)
{
	static const t_vec3	vup = (t_vec3){0, 1, 0};
	t_camera	camera;
	double		theta = degrees_to_radians(vfov * 0.5);
	double		h = tan(theta);
	double		screen_height = 2.0 * h;
	double		screen_width = screen_height * ASPECT_RATIO;

	t_vec3		w = negative_vec(_orient); // lookfrom - lookat
	t_vec3		u = normalize(cross(vup, w)); // 横軸の単位ベクトル
	t_vec3		v = cross(w, u); // 縦軸の単位ベクトル

	camera.origin = _origin;
	camera.horizontal = scal_mul_vec(u, screen_width);
	camera.vertical = scal_mul_vec(v, screen_height);
	camera.higher_left_corner = add_vec(sub_vec(camera.origin, scal_div_vec(camera.horizontal, 2)), sub_vec(scal_div_vec(camera.vertical, 2), w));
	// higher_left_corner = {origin - horizontal/2 } + {vertical/2 - w)} ;
	return (camera);
}

/*
@brief 度数法を弧度法に変換
*/
static double	degrees_to_radians(const double degrees)
{
	double	deno;

	deno = 1.0f / 180.0f;
	return (degrees * M_PI * deno);
}

t_ray	get_ray(t_camera camera, double u, double v)
{
	t_ray	ray;

	ray = construct_ray(camera.origin, 
		sub_vec(add_vec(camera.higher_left_corner, scal_mul_vec(camera.horizontal, u)), add_vec(scal_mul_vec(camera.vertical, v), camera.origin)));
	// {higher_left_corner + u*horizontal}  -  {v*vertical + origin};
	return (ray);
}
