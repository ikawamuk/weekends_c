#include <stdio.h>
#include "define.h"
#include "img.h"
#include "pixcel.h"
#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hit_table_list.h"
#include "camera.h"
#include "util.h"
#include "lambertian.h"
#include "light.h"

t_color ray_color(t_ray ray, t_color back_ground, t_hit_table_list *world, int depth);

void	draw_image(void **mlx, t_img *img, bool ppm_mode)
{
	t_pixcel	pixcel;
	t_camera	camera = construct_camera();

	// set objects in the world
	const t_color		back_ground = construct_color(0, 0, 0);
	t_hit_table_list	world = construct_htl();
	// 地面
	add_htl(&world, gen_sphere(construct_vec(0, -100.5, -2), 100, gen_lambertian(construct_color(0.5, 0.1, 0.1))));
	// もの
	add_htl(&world, gen_sphere(construct_vec(0, 0, -2), 0.5, gen_lambertian(construct_color(0.5, 0.1, 0.1)))); // gen_lambertian(construct_color(0.5, 0, 0)だと環境光にRの要素がないとき真っ黒担って不自然だった！
	add_htl(&world, gen_sphere(construct_vec(1, 0,-2), 0.5, gen_lambertian(construct_color(0.4, 0.7, 0.8))));
	add_htl(&world, gen_sphere(construct_vec(-1,0,-2), 0.5, gen_lambertian(construct_color(0.02, 0.2, 0.02))));
	// ライト
	add_htl(&world, gen_sphere(construct_vec(0, 10, -2), 0.5, gen_light(construct_vec(500, 500, 500)))); // lightの色tの強さは大きさ、距離などの複合で決めるらしい。むずかしい(--;)。

	// Let's draw
	if (ppm_mode)
		printf("P3\n%d %d\n255\n", WINSIZE_X, WINSIZE_Y);
	for (pixcel.y = 0; pixcel.y < WINSIZE_Y; pixcel.y++)
	{
		fprintf(stderr, "\rScanlines remaining: %d ", WINSIZE_Y - pixcel.y - 1);
		for (pixcel.x = 0; pixcel.x < WINSIZE_X; pixcel.x++)
		{
			t_color	pixel_color = construct_color(0, 0, 0);
			for (int s = 0; s < SAMPLES_PER_PIXCEL; ++s)
			{
				double	u = (pixcel.x + random_double(0, 1)) / (WINSIZE_X - 1);
				double	v = (pixcel.y + random_double(0, 1)) / (WINSIZE_Y - 1);
				t_ray ray = get_ray(camera, u, v);
				pixel_color = add_vec(pixel_color, ray_color(ray, back_ground, &world, 0));
			}
			if (ppm_mode)
				write_ppm(get_raw_rgb(pixel_color));
			else
				write_color(*mlx, img, &pixcel, get_raw_rgb(pixel_color));
		}
	}
	fprintf(stderr, "\nDone.\n");
	clear_htl(world);
	return ;
}
