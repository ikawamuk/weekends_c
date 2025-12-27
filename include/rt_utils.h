#ifndef RT_UTILS_H
# define RT_UTILS_H

#include "define.h"
#include "vec3.h"
#include "libft.h"
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

/*
@brief skip_vec()でベクトルがどういった性質か判別するために使用
*/
typedef enum s_is
{
	IS_POINT,
	IS_UNIT,
	IS_COLOR
}	t_is;

double	random_double(double min, double max);
int		random_int(int min, int max);
double	clamp(double x, double min, double max);
double	pow2(double a);
int		skip_spaces(char **ptr);
int		skip_digit(char **ptr);
char	*get_word_line(t_list *line_lst, const char *word);
int		skip_vec(char **ptr, t_is is);
bool	skip_range(char **line, double min, double max);

#endif
