#ifndef MATERIAL_H
# define MATERIAL_H

#include "hit_table.h"
#include "vec3.h"
#include "ray.h"

/*
@param attenuation  Albdoを表す。
@param scattered 散乱レイ
@param surface_pdf_ptr ray_colorで散乱レイを生成するためのptr
*/
typedef struct s_scatter_record
{
	t_color	attenuation;
	t_ray	scattered;
	void	*surface_pdf_ptr;
}	t_scatter_record;

/*
@param scatter scatter_recordを返す
@param emmited 発光色を返す
@param value_surface_pdf 
*/
typedef struct s_material
{
	bool	(*scatter)(void *self, t_hit_record rec, t_scatter_record *srec);
	t_color	(*emitted)(void *self, t_hit_record rec);
	double	(*value_surface_pdf)(void *self, t_hit_record rec, t_ray scattered);
}	t_material;

t_color	emitted_non_light(void *s, t_hit_record rec);

#endif
