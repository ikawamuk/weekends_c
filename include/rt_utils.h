#ifndef UTIL_H
# define UTIL_H

#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include "define.h"
#include "libft.h"

double	random_double(double min, double max);
int		random_int(int min, int max);
double	clamp(double x, double min, double max);
double	pow2(double a);
int		skip_spaces(char **ptr);
int		skip_digit(char **ptr);
char	*get_word_line(t_list *line_lst, const char *word);

#endif
