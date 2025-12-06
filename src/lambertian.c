#include <stdlib.h>
#include "lambertian.h"
#include "util.h"

t_lambertian	construct_lambertian(t_color alb)
{
	t_lambertian	lam;

	lam.mat.scatter = scatter_lambertian;
	lam.albedo = alb;
	return (lam);
}



t_lambertian	*gen_lambertian(t_color alb)
{
	t_lambertian	*p = malloc(sizeof(*p));
	if (!p)
		return (NULL);
	*p = construct_lambertian(alb);
	return (p);
}
