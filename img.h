#ifndef IMG_H
# define IMG_H

#include "define.h"
#include "mlx.h"

typedef struct	s_img {
	void	*id;
	char	*addr;
	int		bits_per_pixcel;
	int		line_size;
	int		endian;
}			t_img;

void	construct_img(t_img *img, void *mlx);

#endif
