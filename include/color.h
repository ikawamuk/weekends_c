#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>
#include "vec3.h"
#include "img.h"
#include "pixcel.h"

int		get_raw_rgb(t_color pixel_color);
void	write_color(void *mlx, t_img *img, t_pixcel *pixcel, int raw_rgb);
void	write_ppm(int raw_rgb);

#endif