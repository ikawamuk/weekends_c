#include "color.h"
#include "mlx.h"
#include "util.h"

int	get_raw_rgb(t_color pixel_color)
{
	int		int_color[3];
	double	double_color[3];

	double_color[0] = sqrt(pixel_color.x);
	double_color[1] = sqrt(pixel_color.y);
	double_color[2] = sqrt(pixel_color.z);
	int_color[0] = 256 * clamp(double_color[0], 0.0, 0.999);
	int_color[1] = 256 * clamp(double_color[1], 0.0, 0.999);
	int_color[2] = 256 * clamp(double_color[2], 0.0, 0.999);
	return ((int_color[0] << 16) | (int_color[1] << 8) | int_color[2]);
}

void	write_color(void *mlx, char *dst, t_color color, bool ppm_mode)
{
	int	raw_rgb = get_raw_rgb(color);

	if (ppm_mode)
		write_ppm(raw_rgb);
	else
		*(unsigned int*)dst = mlx_get_color_value(mlx, raw_rgb);
	return ;
}

void	write_ppm(int raw_rgb)
{
	int r = (raw_rgb >> 16) & 0xFF;
	int g = (raw_rgb >> 8)  & 0xFF;
	int b =  raw_rgb        & 0xFF;
	printf("%d %d %d\n", r, g, b);
}