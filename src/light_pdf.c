#include "pdf.h"
#include "material.h"

static double	value_light_pdf(void *s, t_vec3 direction);
static t_vec3	generate_light_pdf(void *s);

t_light_pdf	construct_light_pdf(t_hit_record rec, t_world world)
{
	t_light_pdf	light;

	light.pdf.value_pdf = value_light_pdf;
	light.pdf.generate_pdf = generate_light_pdf;
	(void)rec;
	(void)world;
	return (light);
}

static double	value_light_pdf(void *s, t_vec3 direction)
{
	t_light_pdf	*self = s;

	(void)self;
	(void)direction;
	return (0);
}

static t_vec3	generate_light_pdf(void *s)
{
	t_light_pdf	*self = s;

	(void)self;
	return (random_unit_vector());
}
