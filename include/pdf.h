#ifndef PDF_H
# define PDF_H

#include <math.h>
#include "define.h"
#include "vec3.h"

typedef struct s_pdf
{
	double	(*value_pdf)(void *self, t_vec3 direction);
}	t_pdf;

typedef struct s_cosine_pdf
{
	t_pdf	pdf;
	t_vec3	onb[3];
}	t_cosine_pdf;

#endif