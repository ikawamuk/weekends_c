#ifndef T_RANGE_H
# define T_RANGE_H

# include <stdbool.h>

typedef struct s_t_range
{
	double	min;
	double	max;
}	t_t_range;

t_t_range	construct_t_range(double _min, double _max);
bool		check_range(const double a, const t_t_range t);

#endif