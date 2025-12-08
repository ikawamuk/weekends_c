#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>
#include "vec3.h"
#include "img.h"

void	write_color(void *mlx, t_img *img, t_color *color_arr);
void	write_ppm(t_color *color_arr);

#endif