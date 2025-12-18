#include "pdf.h"

static double	value_cosine_pdf(void *s, t_vec3 direction);
static t_vec3	generate_cosine_pdf(void *s);

t_cosine_pdf	construct_cosine_pdf(t_vec3 n)
{
	t_cosine_pdf	cosine;

	cosine.pdf.value_pdf = value_cosine_pdf;
	cosine.pdf.generate_pdf = generate_cosine_pdf;
	build_onb(cosine.onb, n);
	return (cosine);
}


#include <stdio.h>
static double	value_cosine_pdf(void *s, t_vec3 direction)
{
	t_cosine_pdf	*self = s;

	return (dot(self->onb[2], normalize(direction)) / M_PI);
}

static t_vec3	generate_cosine_pdf(void *s)
{
	t_cosine_pdf	*self = s;

	return (local_onb(self->onb, random_cosine_direction()));
}
