#include "t_range.h"

t_t_range	construct_t_range(double _min, double _max)
{
	t_t_range	t_range;

	t_range.max = _max;
	t_range.min = _min;
	return (t_range);
}

bool	check_range(const double a, const t_t_range t)
{
	return (t.min < a && a < t.max);
}
