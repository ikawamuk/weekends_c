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

	camera.onb[2] = negative_vec(_orient); // lookfrom - lookat
	camera.onb[0] = normalize(cross(vup, camera.onb[2])); // 横軸の単位ベクトル
	camera.onb[1] = cross(camera.onb[2], camera.onb[0]); // 縦軸の単位ベクトル

	camera.origin = _origin;
	camera.horizontal = scal_mul_vec(camera.onb[0], screen_width * FOCUS_DIST);
	camera.vertical = scal_mul_vec(camera.onb[1], screen_height * FOCUS_DIST);
	camera.higher_left_corner = add_vec(sub_vec(camera.origin, scal_div_vec(camera.horizontal, 2)), sub_vec(scal_div_vec(camera.vertical, 2), scal_mul_vec(camera.onb[2], FOCUS_DIST)));
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
