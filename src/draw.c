#include <stdio.h>
#include "define.h"
#include "pixcel.h"
#include "img.h"
#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "hit_table_list.h"
#include "camera.h"
#include "util.h"

t_color				ray_color(t_ray ray, t_color back_ground, const t_hit_table_list *world, int depth);
t_hit_table_list	set_world(void);
static t_color		accumulate_pixcel_color(t_pixcel pixcel, t_camera camera, t_color back_ground, const t_hit_table_list *world);

void	draw(void **mlx, t_img *img, bool ppm_mode)
{
	t_pixcel	pixcel;
	t_camera	camera = construct_camera();

	// set objects in the world
	const t_color		back_ground = construct_color(0.5, 0.5, 0.7);
	t_hit_table_list	world = set_world();

	// Let's draw
	if (ppm_mode)
		printf("P3\n%d %d\n255\n", WINSIZE_X, WINSIZE_Y);
	for (pixcel.y = 0; pixcel.y < WINSIZE_Y; pixcel.y++)
	{
		fprintf(stderr, "\rScanlines remaining: %d ", WINSIZE_Y - pixcel.y - 1);
		for (pixcel.x = 0; pixcel.x < WINSIZE_X; pixcel.x++)
		{
			t_color	pixcel_color = accumulate_pixcel_color(pixcel, camera, back_ground, &world);
			if (ppm_mode)
				write_ppm(get_raw_rgb(pixcel_color));
			else
				write_color(*mlx, img, &pixcel, get_raw_rgb(pixcel_color));
		}
	}
	fprintf(stderr, "\nDone.\n");
	clear_htl(world);
	return ;
}

static t_color	accumulate_pixcel_color(t_pixcel pixcel, t_camera camera, t_color back_ground, const t_hit_table_list *world)
{
	t_color	pixcel_color = construct_color(0, 0, 0);
	for (int s = 0; s < SAMPLES_PER_PIXCEL; ++s)
	{
		double	u = (pixcel.x + random_double(0, 1)) / (WINSIZE_X - 1);
		double	v = (pixcel.y + random_double(0, 1)) / (WINSIZE_Y - 1);
		t_ray ray = get_ray(camera, u, v);
		pixcel_color = add_vec(pixcel_color, ray_color(ray, back_ground, world, 0));
	}
	return (pixcel_color);
}
