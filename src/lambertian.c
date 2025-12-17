#include <stdlib.h>
#include "lambertian.h"
#include "util.h"

t_lambertian	construct_lambertian(t_color alb)
{
	t_lambertian	lam;

	lam.material.scatter = scatter_lambertian;
	lam.material.emitted = emitted_non_light;
	lam.albedo = construct_color(alb.x, alb.y, alb.z);
	return (lam);
}

bool	scatter_lambertian(void *s, t_hit_record rec, t_scatter_record *srec)
{
	t_lambertian	*self = s;

	// １＝1, 2はPDFの仕事なのでray_color()に移動。
	// 1.散乱レイを生成
	t_vec3	onb[3];
	build_onb(onb, rec.normal);
	t_vec3	scatter_direction = local_onb(onb, random_cosine_direction());
	if (dot(rec.normal, rec.ray_in.direct) > 0)
		scatter_direction = negative_vec(scatter_direction);
	srec->scattered = construct_ray(rec.p, scatter_direction);

	// 2.サンプリングPDFを代入
	srec->surface_pdf = dot(onb[2], normalize(srec->scattered.direct))/ M_PI; // + 0.5 * light_pdf()

	// 反射率Albedoを代入
	srec->attenuation = self->albedo;
	return (true);
}

t_lambertian	*gen_lambertian(t_color alb)
{
	t_lambertian	*p = malloc(sizeof(*p));
	if (!p)
		return (NULL);
	*p = construct_lambertian(alb);
	return (p);
}
