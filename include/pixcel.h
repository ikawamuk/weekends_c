#ifndef PIXCEL_H
# define PIXCEL_H

#include "vec3.h"

typedef struct s_pixcel
{
	t_color	color;
	t_vec3	normal;
	t_color	albedo;
}	t_pixcel;

#endif
