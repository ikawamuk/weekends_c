#ifndef MATERIAL_H
# define MATERIAL_H

#include "hit_table.h"
#include "vec3.h"
#include "ray.h"

/*
@param attenuation  Albdoを表す。
@param scattered 散乱レイ
@param surface_pdf 物質による散乱分布の確率密度（ランバートならcosに比例）
@param sampling_pdf サンプリングするレイの確率密度（surface_pdfとlight_pdfの線形和）
*/
typedef struct s_scatter_record
{
	t_color	attenuation;
	t_ray	scattered;
	double	surface_pdf;
	double	sampling_pdf;
}	t_scatter_record;

typedef struct s_material
{
	bool	(*scatter)(void *self, t_hit_record rec, t_scatter_record *srec);
	t_color	(*emitted)(void *self, t_hit_record rec);
	double	(*surface_pdf)(void *self, t_hit_record rec, t_ray scattered);
}	t_material;

t_color	emitted_non_light(void *s, t_hit_record rec);

#endif
