#include <stdlib.h>
#include "metal.h"
#include "rt_utils.h"
#include "pdf.h"
bool	scatter_metal(void *s, t_hit_record *rec, t_scatter_record *srec);


typedef struct s_metal_pdf
{
	t_pdf	pdf;
	t_vec3	normal;
	t_ray	ray_in;
	double	fuzz;
}	t_metal_pdf;

double	metal_pdf(void *s, t_hit_record rec, t_ray scattered);
t_metal_pdf	construct_metal_pdf(t_vec3 normal, t_ray ray_in, double fuzz);

t_metal	construct_metal(t_color alb, double fuzz)
{
	t_metal	metal;

	metal.material.scatter = scatter_metal;
	metal.material.emitted = emitted_non_light;
	metal.material.value_surface_pdf = metal_pdf;
	metal.albedo = alb;
	metal.fuzz = fuzz + 0.05;
	return (metal);
}


double	metal_pdf(void *s, t_hit_record rec, t_ray scattered)
{
	t_metal	*self = s;

	if (self->fuzz <= 0.0)
		return (INFINITY);
	t_vec3	reflect_normal = dot(rec.normal, rec.ray_in.direct) > 0 ? negative_vec(rec.normal) : rec.normal;

	t_metal_pdf	pdf = construct_metal_pdf(reflect_normal, rec.ray_in, self->fuzz);
	return (pdf.pdf.value_pdf(&pdf, scattered.direct));
}

double	value_metal_pdf(void *s, t_vec3 direction)
{
	t_metal_pdf	*self = s;

	if (self->fuzz <= 0.0)
		return (1.0);
	t_vec3 reflected = reflect(normalize(self->ray_in.direct), self->normal);
	t_vec3 target = normalize(direction);
	t_vec3 center = normalize(reflected);
	t_vec3 diff = sub_vec(target, center);
	if (length_vec(diff) <= self->fuzz)
		return (1.0 / (M_PI * self->fuzz * self->fuzz));
	return (0.1);
}

t_vec3	random_metal_pdf(void *s)
{
	t_metal_pdf	*self = s;

	t_vec3	reflected = reflect(normalize(self->ray_in.direct), self->normal);
	return (add_vec(reflected, scal_mul_vec(random_in_unit_sphere(), self->fuzz)));
}

t_metal_pdf	construct_metal_pdf(t_vec3 normal, t_ray ray_in, double fuzz)
{
	t_metal_pdf	metal_pdf;

	metal_pdf.pdf.random_pdf = random_metal_pdf;
	metal_pdf.pdf.value_pdf = value_metal_pdf;
	metal_pdf.normal = normal;
	metal_pdf.ray_in = ray_in;
	metal_pdf.fuzz = fuzz;
	return (metal_pdf);
}

t_metal_pdf	*gen_metal_pdf(t_vec3 normal, t_ray ray_in, double fuzz)
{
	t_metal_pdf	*p = malloc(sizeof(t_metal_pdf));
	if (!p)
		return (NULL);
	*p = construct_metal_pdf(normal, ray_in, fuzz);
	return (p);
}

bool	scatter_metal(void *s, t_hit_record *rec, t_scatter_record *srec)
{
	t_metal	*self = s;

	srec->attenuation = self->albedo;
	t_vec3	reflect_normal = dot(rec->normal, rec->ray_in.direct) > 0 ? negative_vec(rec->normal) : rec->normal;
	t_metal_pdf	*metal_pdf = gen_metal_pdf(reflect_normal, rec->ray_in, self->fuzz);
	
	srec->surface_pdf_ptr = metal_pdf;
	srec->is_specular = false;
	return (true);
}

t_metal	*gen_metal(t_color alb, double fuzz)
{
	t_metal	*p = malloc(sizeof(*p));
	if (!p)
		return (NULL);
	*p = construct_metal(alb, fuzz);
	return (p);
}