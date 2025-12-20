#ifndef RANGE_H
# define RANGE_H

# include <stdbool.h>

typedef struct s_range
{
	double	min;
	double	max;
}	t_range;

t_range	construct_range(double _min, double _max);
bool	check_range(double x, t_range range);

#endif