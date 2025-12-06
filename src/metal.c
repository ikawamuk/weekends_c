#include <stdlib.h>
#include "metal.h"

t_metal	construct_metal(t_color alb)
{
	t_metal	met;

	met.mat.scatter = scatter_metal;
	met.albedo = alb;
}

t_metal	*gen_metal(t_color alb)
{
	t_metal	*p = malloc(sizeof(*p));
	if (!p)
		return (NULL);
	*p = construct_metal(alb);
	return (p);
}