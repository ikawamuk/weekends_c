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
static t_color		accumulate_pixcel_color(int x, int y, t_camera camera, const t_world *world);

void	draw(void **mlx, t_img *img, bool ppm_mode)
{
	t_color		*color_arr = malloc(PIXCELS_NUM * sizeof(t_color));
	t_camera	camera = construct_camera(construct_vec(0, 1, 0), normalize(construct_vec(0, -0.3, -1)), 120);

	// set objects in the world
	t_world	world = set_world();

	// Let's draw
	if (ppm_mode)
		printf("P3\n%d %d\n255\n", WINSIZE_X, WINSIZE_Y);
	for (int y = 0; y < WINSIZE_Y; y++)
	{
		int yy = y * WINSIZE_X;
		fprintf(stderr, "\rScanlines remaining: %d/%d ", y + 1, WINSIZE_Y);
		for (int x = 0; x < WINSIZE_X; x++)
		{
			color_arr[yy + x] = accumulate_pixcel_color(x, y, camera, &world);
		}
	}
	if (ppm_mode)
		write_ppm(color_arr);
	else
		write_color(*mlx, img, color_arr);
	free(color_arr);
	fprintf(stderr, "\nDone.\n");
	clear_htl(world.objects);
	return ;
}

static t_color	accumulate_pixcel_color(int x, int y, t_camera camera, const t_world *world)
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
	return (scal_mul_vec(pixcel_color, scale));
}
