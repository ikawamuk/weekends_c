#ifndef PDF_H
# define PDF_H

#include <math.h>
#include "define.h"
#include "vec3.h"
#include "rt_utils.h"
#include "world.h"

/*
@param value_pdf PDFの値を出す
@param generate_pdf　PDFに沿ったvet3を返す
*/
typedef struct s_pdf
{
	double	(*value_pdf)(void *self, t_vec3 direction);
	t_vec3	(*generate_pdf)(void *self);
}	t_pdf;

typedef struct s_cosine_pdf
{
	t_pdf	pdf;
	t_vec3	onb[3];
}	t_cosine_pdf;

t_cosine_pdf	construct_cosine_pdf(t_vec3 n);

typedef struct s_light_pdf
{
	t_pdf				pdf;
	t_hit_table_list	list;
	t_point3			p;
}	t_light_pdf;

t_light_pdf	construct_light_pdf(t_hit_record rec, t_world world);

typedef struct s_mixture_pdf
{
	t_pdf	pdf;
	void	*surface_pdf;
	void	*light_pdf;
}	t_mixture_pdf;

t_mixture_pdf	construct_mixture_pdf(void *surface_pdf, void *light_pdf);

#endif