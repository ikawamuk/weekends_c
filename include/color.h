#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>
#include <stdbool.h>
#include "vec3.h"
#include "img.h"

int		get_raw_rgb(t_color pixel_color);
void	write_color(void *mlx, char *dst, t_color color, bool ppm_mode);
void	write_ppm(int raw_rgb);

#endif