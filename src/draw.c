#include <stdio.h>
#include "define.h"
#include "img.h"
#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "hit_table_list.h"
#include "camera.h"
#include "rt_utils.h"
#include "world.h"

t_color				phong_color(t_ray ray, const t_world *world);
t_color				ray_color(t_ray ray, const t_world *world, int depth);
static t_color		get_pixcel_color(int x, int y, const t_world *world);
static void			write_loop(void ** mlx, t_img *img, t_color *color_arr, bool ppm_mode);
static void			pixcel_color_loop(t_color *color_arr, const t_world *world);

void	draw(const t_world *world, void **mlx, t_img *img, bool ppm_mode)
{
	t_color		*color_arr = malloc(WINSIZE_X * WINSIZE_Y * sizeof(t_color));

	pixcel_color_loop(color_arr, world);
	write_loop(mlx, img, color_arr, ppm_mode);
	free(color_arr);
	return ;
}

static void	pixcel_color_loop(t_color *color_arr, const t_world *world)
{
	for (int y = 0; y < WINSIZE_Y; y++)
	{
		int yy = y * WINSIZE_X;
		fprintf(stderr, "\rScanlines remaining: %d ", WINSIZE_Y - y - 1);
		for (int x = 0; x < WINSIZE_X; x++)
			color_arr[yy + x] = get_pixcel_color(x, y, world);
	}
	fprintf(stderr, "\nDone.\n");
	return ;
}

static t_color	get_pixcel_color(int x, int y, const t_world *world)
{
	static const double	scale = 1.0 / SAMPLES_PER_PIXCEL;
	t_color	pixcel_color = constant_vec(0.0);
	// if (is_phong)
	// 	return (phong_color(get_ray(world->camera, (double)x / (WINSIZE_X - 1), \
	// 	(double)y / (WINSIZE_Y - 1)), world));
	for (int s = 0; s < SAMPLES_PER_PIXCEL; ++s)
	{
		double	u = (x + random_double(0, 1)) / (WINSIZE_X - 1);
		double	v = (y + random_double(0, 1)) / (WINSIZE_Y - 1);
		t_ray ray = get_ray(world->camera, u, v);
		if (is_phong)
			pixcel_color = add_vec(pixcel_color, phong_color(ray, world));
		else
			pixcel_color = add_vec(pixcel_color, ray_color(ray, world, 0));
	}
	pixcel_color = scal_mul_vec(pixcel_color, scale);
	return (pixcel_color);
}

static void	write_loop(void ** mlx, t_img *img, t_color *color_arr, bool ppm_mode)
{
	if (ppm_mode)
		printf("P3\n%d %d\n255\n", WINSIZE_X, WINSIZE_Y);
	for (int y = 0; y < WINSIZE_Y; y++)
	{
		int yy = y * WINSIZE_X;
		for (int x = 0; x < WINSIZE_X; x++)
		{
			char *dst = img->addr + (y * img->line_size + x * img->bytes_per_pixcel);
			write_color(*mlx, dst, color_arr[yy + x], ppm_mode);
		}
	}
	return ;
}
