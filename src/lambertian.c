#include <stdlib.h>
#include "lambertian.h"
#include "util.h"
#include "pdf.h"

t_lambertian	construct_lambertian(t_color alb)
{
	t_lambertian	lam;

	lam.material.scatter = scatter_lambertian;
	lam.material.emitted = emitted_non_light;
	lam.material.surface_pdf = lambertian_pdf;
	lam.albedo = construct_color(alb.x, alb.y, alb.z);
	return (lam);
}

/*
@brief 1.散乱方向を生成 2.散乱レイを代入 3.サンプリングPDFを代入 4.反射率Albedoを代入

*/
bool	scatter_lambertian(void *s, t_hit_record rec, t_scatter_record *srec)
{
	t_lambertian	*self = s;

	t_vec3	onb[3];
	build_onb(onb, rec.normal);
	t_vec3	scatter_direction = local_onb(onb, random_cosine_direction());
	if (dot(rec.normal, rec.ray_in.direct) > 0)
		scatter_direction = negative_vec(scatter_direction);

	// srec->sampling_pdf = dot(onb[2], normalize(scatter_direction))/ M_PI;
	srec->scattered = construct_ray(rec.p, scatter_direction);
	srec->sampling_pdf = self->material.surface_pdf(self, rec, srec->scattered);
	srec->attenuation = self->albedo;
	return (true);
}

double	lambertian_pdf(void *s, t_hit_record rec, t_ray scattered)
{
	t_lambertian	*self = s;

	(void)self;
	double	cosine = dot(rec.normal, normalize(scattered.direct));
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
