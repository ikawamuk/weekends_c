#include <stdio.h>
#include "define.h"
#include "img.h"
#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "hit_table_list.h"
#include "camera.h"
#include "util.h"
#include "world.h"

t_color				ray_color(t_ray ray, const t_world *world, int depth);
t_world				set_world(void);
static t_color		get_pixcel_color(int x, int y, t_camera camera, const t_world *world);
static void			write_loop(void ** mlx, t_img *img, t_color *color_arr, bool ppm_mode);
static void			pixcel_color_loop(t_color *color_arr, t_camera camera, t_world *world);

void	draw(void **mlx, t_img *img, bool ppm_mode)
{
	// set objects in the world
	t_world		world = set_world();
	t_camera	camera = construct_camera(construct_vec(0, 1, 0), normalize(construct_vec(0, -0.3, -1)), 70);
	t_color		*color_arr = malloc(WINSIZE_X * WINSIZE_Y * sizeof(t_color));

	pixcel_color_loop(color_arr, camera, &world);
	write_loop(mlx, img, color_arr, ppm_mode);
	clear_htl(world.objects);
	free(color_arr);
	return ;
}

static void	write_loop(void ** mlx, t_img *img, t_color *color_arr, bool ppm_mode)
{
	if (ppm_mode)
		printf("P3\n%d %d\n255\n", WINSIZE_X, WINSIZE_Y);
	int yy = 0;
	for (int y = 0; y < WINSIZE_Y; y++)
	{
		for (int x = 0; x < WINSIZE_X; x++)
		{
			char *dst = img->addr + (y * img->line_size + x * img->bytes_per_pixcel);
			write_color(*mlx, dst, color_arr[yy + x], ppm_mode);
		}
		yy += WINSIZE_X;
	}
	return ;
}

static void	pixcel_color_loop(t_color *color_arr, t_camera camera, t_world *world)
{
	int	yy = 0;
	for (int y = 0; y < WINSIZE_Y; y++)
	{
		fprintf(stderr, "\rScanlines remaining: %d ", WINSIZE_Y - y - 1);
		for (int x = 0; x < WINSIZE_X; x++)
			color_arr[yy + x] = get_pixcel_color(x, y, camera, world);
		yy += WINSIZE_X;
	}
	fprintf(stderr, "\nDone.\n");
}

static t_color	get_pixcel_color(int x, int y, t_camera camera, const t_world *world)
{
	static const double	scale = 1.0 / SAMPLES_PER_PIXCEL;
	t_color	pixcel_color = construct_color(0, 0, 0);
	for (int s = 0; s < SAMPLES_PER_PIXCEL; ++s)
	{
		double	u = (x + random_double(0, 1)) / (WINSIZE_X - 1);
		double	v = (y + random_double(0, 1)) / (WINSIZE_Y - 1);
		t_ray ray = get_ray(camera, u, v);
		pixcel_color = add_vec(pixcel_color, ray_color(ray, world, 0));
	}
	pixcel_color = scal_mul_vec(pixcel_color, scale);
	return (pixcel_color);
}
