#include <stdbool.h>
#include <stdlib.h>
#include "define.h"
#include "img.h"

typedef struct s_hook_var
{
	void	*mlx;
	void	*win;
}	t_hook_var;

void	draw(void **mlx, t_img *img, bool ppm_mode);

void	initialize(t_hook_var *var, t_img *img)
{
	var->mlx = mlx_init();
	var->win = mlx_new_window(var->mlx, WINSIZE_X, WINSIZE_Y, "Testy!");
	construct_img(img, var->mlx);
	return ;
}

int close_window(void *param)
{
	t_hook_var *vars = (t_hook_var*)param;

	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

int	main(void)
{
	t_hook_var	var;
	t_img		img;
	bool		ppm_mode = false;

	if (!ppm_mode)
		initialize(&var, &img);
	draw(&var.mlx, &img, ppm_mode);
	if (ppm_mode)
		return (0);
	mlx_put_image_to_window(var.mlx, var.win, img.id, 0, 0);
	mlx_hook(var.win, 17, 0L, close_window, &var);
	mlx_loop(var.mlx);
	return (0);
}
