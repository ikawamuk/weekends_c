#include "pdf.h"
#include "material.h"

static double	value_light_pdf(void *s, t_vec3 direction);
static t_vec3	generate_light_pdf(void *s);

t_light_pdf	construct_light_pdf(t_hit_record rec, t_world world)
{
	t_light_pdf	light_;

	light_.pdf.value_pdf = value_light_pdf;
	light_.pdf.generate_pdf = generate_light_pdf;
	light_.list = world.lights;
	light_.p = rec.p;
	return (light_);
}

static double	value_light_pdf(void *s, t_vec3 direction)
{
	t_light_pdf	*self = s;

	double	result = self->list.hit_table.pdf_value(&self->list, self->p, direction);
	return (result);
}

static t_vec3	generate_light_pdf(void *s)
{
	t_light_pdf	*self = s;

	return (self->list.hit_table.random(&self->list, self->p));
}
