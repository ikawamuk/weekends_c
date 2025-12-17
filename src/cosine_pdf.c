#include "pdf.h"

t_cosine_pdf	construct_cosine_pdf(t_vec3 n)
{
	t_cosine_pdf	cosine;

	cosine.pdf.value_pdf = value_cosine_pdf;
	build_onb(cosine.onb, n);
}

double	value_cosine_pdf(void *s, t_vec3 direction)
{
	t_cosine_pdf	*self = s;

	return (dot(self->onb[2], normalize(direction))/ M_PI);
}
