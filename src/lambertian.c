#include <stdlib.h>
#include "lambertian.h"
#include "util.h"

t_lambertian	construct_lambertian(t_color alb)
{
	t_lambertian	lam;

	lam.material.scatter = scatter_lambertian;
	lam.material.emitted = emitted_non_light;
	lam.material.surface_pdf = lambertian_pdf;
	lam.albedo = construct_color(alb.x, alb.y, alb.z);
	return (lam);
}

bool	scatter_lambertian(void *s, t_hit_record rec, t_scatter_record *srec)
{
	t_lambertian	*self = s;

	// 散乱レイを生成
	t_vec3	scatter_direction = add_vec(rec.normal , random_unit_vector());
	if (dot(rec.normal, rec.ray_in.direct) > 0)
		scatter_direction = negative_vec(scatter_direction);
	srec->scattered = construct_ray(rec.p, scatter_direction);

	// サンプリングPDFを代入
	srec->sampling_pdf = dot(normalize(rec.normal), normalize(srec->scattered.direct)) / M_PI;

	// 反射率Albedoを代入
	srec->attenuation = self->albedo;
	return (true);
}

double	lambertian_pdf(void *s, t_hit_record rec, t_ray scattered)
{
	t_lambertian	*self = s;

	(void)self;
	double	cosine = dot(normalize(rec.normal), normalize(scattered.direct));
	return (cosine < 0 ? 0 : cosine / M_PI);
}

t_lambertian	*gen_lambertian(t_color alb)
{
	t_lambertian	*p = malloc(sizeof(*p));
	if (!p)
		return (NULL);
	*p = construct_lambertian(alb);
	return (p);
}
