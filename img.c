#include "img.h"

void	construct_img(t_img *img, void *mlx)
{
	img->id = mlx_new_image(mlx, WINSIZE_X, WINSIZE_Y);
	img->addr = mlx_get_data_addr(
		img->id, \
		&img->bits_per_pixcel, \
		&img->line_size, \
		&img->endian\
	);
	return ;
}
