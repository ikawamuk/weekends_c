#include <stdbool.h>
#include "define.h"
#include "img.h"

void	draw(void **mlx, t_img *img, bool ppm_mode);

void	initialize(void **mlx, void **win, t_img *img)
{
	*mlx = mlx_init();
	*win = mlx_new_window(*mlx, WINSIZE_X, WINSIZE_Y, "Testy!");
	construct_img(img, *mlx);
	return ;
}

int	main(void)
{
	void	*mlx;
	void	*win;
	t_img	img;
	bool	ppm_mode = false;

	if (!ppm_mode)
		initialize(&mlx, &win, &img);
	draw(&mlx, &img, ppm_mode);
	if (ppm_mode)
		return (0);
	mlx_put_image_to_window(mlx, win, img.id, 0, 0);
	mlx_loop(mlx);
	mlx_destroy_window(mlx, win);
	return (0);
}
