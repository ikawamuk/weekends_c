#include <stdlib.h>
#include "light.h"
#include "pdf.h"

t_light	construct_light(t_color emit)
{
	t_light	light;

	light.material.scatter = scatter_light;
	light.material.emitted = emitted_light;
	light.emit_color = scal_mul_vec(emit, 100);
	return (light);
}

bool	scatter_light(void* s, t_hit_record *rec, t_scatter_record *srec)
{
	(void)s;
	(void)rec;
	(void)srec;
	return (false);
}

t_color	emitted_light(void *s, t_hit_record rec)
{
	t_light	*self = s;
	if (dot(rec.normal, rec.ray_in.direct) > 0)
		return (construct_vec(1.0, 0, 0));
	return (self->emit_color);
}

t_light	*gen_light(t_color emit)
{
	t_light	*p = malloc(sizeof(*p));
	if (!p)
		return (NULL);
	*p = construct_light(emit);
	return (p);
}

