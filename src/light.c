#include <stdlib.h>
#include "light.h"

t_light	construct_light(t_color emit)
{
	t_light	light;

	light.material.scatter = scatter_light;
	light.material.emitted = emitted_light;
	light.emit_color = emit;
	return (light);
}

bool	scatter_light(void* s, t_hit_record rec, t_color *att, t_ray *sca)
{
	(void)s;
	(void)rec;
	(void)att;
	(void)sca;
	return (false);
}

t_color	emitted_light(void *s, t_hit_record rec)
{	
	t_light	*self = s;
	(void)rec;
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

