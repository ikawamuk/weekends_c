#include "material.h"

t_color	emitted_non_light(void *s, t_hit_record rec)
{
	(void)s;
	(void)rec;
	return (construct_vec(0, 0, 0));
}
