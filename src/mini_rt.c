// #include "define.h"
#include <stdbool.h>
bool	is_phong = false;
#include "img.h"
#include "world.h"
#include <stdlib.h>

#include <stdio.h>

typedef struct s_hook_var
{
	void	*mlx;
	void	*win;
}	t_hook_var;

int		set_world(t_world *world, const char *rt_file);
void	clear_world(t_world *world);
void	draw(const t_world *world, void **mlx, t_img *img, bool ppm_mode);

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
	free(vars->mlx);
	exit(0);
	return (0);
}

int	mini_rt(int argc, char *argv[])
{
	t_hook_var	var;
	t_img		img;
	t_world		world;
	bool		ppm_mode = false;

	if (argc == 1)
		return (fprintf(stderr, "NEED .rt FILE AS AN ARGUMENT\n"), \
		EXIT_FAILURE);

	// 後で消す。フォンの切り替えスイッチ
	if (3 <= argc)
		is_phong = true;


	if (set_world(&world, argv[1]))
		return (EXIT_FAILURE);
	if (!ppm_mode)
		initialize(&var, &img);
	draw(&world, &var.mlx, &img, ppm_mode);
	clear_world(&world);
	if (ppm_mode)
		return (0);
	mlx_put_image_to_window(var.mlx, var.win, img.id, 0, 0);
	mlx_hook(var.win, 17, 0L, close_window, &var);
	mlx_loop(var.mlx);
	return (0);
}
