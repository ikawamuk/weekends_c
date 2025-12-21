#include "pdf.h"

static double	value_mixture_pdf(void *s, t_vec3 direction);
static t_vec3	random_mixture_pdf(void *s);


#include <stdio.h>
t_mixture_pdf	construct_mixture_pdf(void *surface_pdf, void *light_pdf)
{
	t_mixture_pdf	mixture;

	mixture.pdf.value_pdf = value_mixture_pdf;
	mixture.pdf.random_pdf = random_mixture_pdf;
	mixture.surface_pdf = surface_pdf;
	mixture.light_pdf = light_pdf;
	return (mixture);
}

static double	value_mixture_pdf(void *s, t_vec3 direction)
{
	t_mixture_pdf	*self = s;
	t_pdf			*surface_pdf = self->surface_pdf;
	t_pdf			*light_pdf = self->light_pdf;

	if (!light_pdf)
		return (surface_pdf->value_pdf(surface_pdf, direction));
	return (0.5 * surface_pdf->value_pdf(surface_pdf, direction) + 0.5 * light_pdf->value_pdf(light_pdf, direction));
}

static t_vec3	random_mixture_pdf(void *s)
{
	t_mixture_pdf	*self = s;
	t_pdf			*surface_pdf = self->surface_pdf;
	t_pdf			*light_pdf = self->light_pdf;

	if (!light_pdf || random_double(0, 1) > 0.5)
		return (surface_pdf->random_pdf(surface_pdf));
	return (light_pdf->random_pdf(light_pdf));
}
