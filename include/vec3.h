#ifndef VEC3_H
# define VEC3_H

#include "math.h"

typedef struct s_vec3 t_vec3;

struct s_vec3
{
	double	x;
	double	y;
	double	z;
};

t_vec3	construct_vec(double e0, double e1, double e2);
t_vec3	negative_vec(t_vec3 vec);
t_vec3	add_vec(t_vec3 lhs, t_vec3 rhs);
t_vec3	sub_vec(t_vec3 lhs, t_vec3 rhs);
t_vec3	mul_vec(t_vec3 lhs, t_vec3 rhs);
t_vec3	div_vec(t_vec3 lhs, t_vec3 rhs);
t_vec3	scal_mul_vec(t_vec3 lhs, double rhs);
t_vec3	scal_div_vec(t_vec3 lhs, double rhs);
double	length_vec(t_vec3 vec);
double	length_squared_vec(t_vec3 vec);
double	dot(t_vec3 lhs, t_vec3 rhs);
t_vec3	cross(t_vec3 lhs, t_vec3 rhs);
t_vec3	normalize(t_vec3 vec);
t_vec3	random_vec(double min, double max);
t_vec3	random_in_unit_sphere(void);
t_vec3	random_unit_vector(void);
t_vec3	random_cosine_direction(void);
void	build_onb(t_vec3 onb[3], t_vec3 n);
t_vec3	local_onb(t_vec3 onb[3], t_vec3 a);
t_vec3	reflect(t_vec3 v, t_vec3 n);
t_vec3	constant_vec(double d);
double	axis_vec(t_vec3 vec, int axis);
t_vec3	get_vec(char **line);

typedef t_vec3 t_point3;
typedef t_vec3 t_color;

t_color	construct_color(double e0, double e1, double e2);

#endif
