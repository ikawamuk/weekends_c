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
t_vec3	negative_vec(const t_vec3 vec);
t_vec3	add_vec(const t_vec3 lhs, const t_vec3 rhs);
t_vec3	sub_vec(const t_vec3 lhs, const t_vec3 rhs);
t_vec3	mul_vec(const t_vec3 lhs, const t_vec3 rhs);
t_vec3	div_vec(const t_vec3 lhs, const t_vec3 rhs);
t_vec3	scal_mul_vec(const t_vec3 lhs, const double rhs);
t_vec3	scal_div_vec(const t_vec3 lhs, const double rhs);
double	length_vec(const t_vec3 vec);
double	length_squared_vec(const t_vec3 vec);
double	dot(const t_vec3 lhs, const t_vec3 rhs);
t_vec3	cross(const t_vec3 lhs, const t_vec3 rhs);
t_vec3	normalize(const t_vec3 vec);
t_vec3	random_vec(double min, double max);
t_vec3	random_in_unit_sphere(void);
t_vec3	random_unit_vector(void);
t_vec3	reflect(t_vec3 v, t_vec3 n);

typedef t_vec3 t_point3;
typedef t_vec3 t_color;

#endif
