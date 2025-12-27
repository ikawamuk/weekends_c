#include "range.h"

t_range	construct_range(double _min, double _max)
{
	t_range	range;

	range.min = _min;
	range.max = _max;
	return (range);
}

bool	check_range(double x, t_range range)
{
	return (range.min < x && x < range.max);
}
