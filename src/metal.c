#include <stdlib.h>
#include "metal.h"

t_metal	construct_metal(t_color alb)
{
	t_metal	met;

	// met.material.scatter = scatter_metal;
	// met.material.elimitted = emmited_non_light;
	met.albedo = construct_vec(alb.x, alb.y, alb.z);
}

t_metal	*gen_metal(t_color alb)
{
	t_metal	*p = malloc(sizeof(*p));
	if (!p)
		return (NULL);
	*p = construct_metal(alb);
	return (p);
}