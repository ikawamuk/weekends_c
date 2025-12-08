#include "color.h"
#include "mlx.h"
#include "util.h"

static int	get_raw_rgb(t_color pixel_color)
{
	int		int_color[3];
	double	double_color[3];

	// printf("pixcel_colorR: %f\n", pixel_color.x);
	double_color[0] = sqrt(pixel_color.x);
	double_color[1] = sqrt(pixel_color.y);
	double_color[2] = sqrt(pixel_color.z);
	// printf("double_colorR: %f\n", double_color[0]);
	int_color[0] = 256 * clamp(double_color[0], 0.0, 0.999);
	int_color[1] = 256 * clamp(double_color[1], 0.0, 0.999);
	int_color[2] = 256 * clamp(double_color[2], 0.0, 0.999);
	// printf("int_colorR: %d\n", int_color[0]);
	return ((int_color[0] << 16) | (int_color[1] << 8) | int_color[2]);
}

#include <stdio.h>
void	write_color(void *mlx, t_img *img, t_color *color_arr)
{
	for (int y = 0; y < WINSIZE_Y; y++)
	{
		int yy = y * WINSIZE_X;
		for (int x = 0; x < WINSIZE_X; x++)
		{
			int	raw_rgb = get_raw_rgb(color_arr[yy + x]);
			int	mlx_color = mlx_get_color_value(mlx, raw_rgb);
			char *dst = img->addr + (y * img->line_size + x * (img->bits_per_pixcel / 8));
			*(unsigned int*)dst = mlx_color;
		}
	}
	return ;
}

void	write_ppm(t_color *color_arr)
{
	for (int y = 0; y < WINSIZE_Y; y++)
	{
		int yy = y * WINSIZE_X;
		for (int x = 0; x < WINSIZE_X; x++)
		{
			int	raw_rgb = get_raw_rgb(color_arr[yy + x]);
			int r = (raw_rgb >> 16) & 0xFF;
			int g = (raw_rgb >> 8)  & 0xFF;
			int b =  raw_rgb        & 0xFF;
			printf("%d %d %d\n", r, g, b);
		}
	}
	return ;
}

