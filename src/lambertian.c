#include <stdlib.h>
#include "lambertian.h"
#include "util.h"
#include "pdf.h"

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




	// 2.サンプリングPDFを代入
	t_vec3			reflect_normal = dot(rec.normal, rec.ray_in.direct) > 0 ? negative_vec(rec.normal) : rec.normal;
	t_cosine_pdf	cos_pdf = construct_cosine_pdf(reflect_normal);
	srec->scattered = construct_ray(rec.p, cos_pdf.pdf.generate_pdf(&cos_pdf));
	srec->surface_pdf = cos_pdf.pdf.value_pdf(&cos_pdf, srec->scattered.direct); // + 0.5 * light_pdf()
	// 1.散乱レイを生成
	

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
