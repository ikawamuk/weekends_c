#include "vec3.h"
#include "util.h"

t_vec3	construct_vec(double e0, double e1, double e2)
{
	t_vec3	vec;

	vec.x = e0;
	vec.y = e1;
	vec.z = e2;
	return (vec);
}

t_vec3	negative_vec(t_vec3 vec)
{
	t_vec3	result;

	result.x = -vec.x;
	result.y = -vec.y;
	result.z = -vec.z;
	return (result);
}

t_vec3	add_vec(t_vec3 lhs, t_vec3 rhs)
{
	t_vec3	result;

	result.x = lhs.x + rhs.x;
	result.y = lhs.y + rhs.y;
	result.z = lhs.z + rhs.z;
	return (result);
}

t_vec3	sub_vec(t_vec3 lhs, t_vec3 rhs)
{
	t_vec3	result;

	result.x = lhs.x - rhs.x;
	result.y = lhs.y - rhs.y;
	result.z = lhs.z - rhs.z;
	return (result);
}

t_vec3	mul_vec(t_vec3 lhs, t_vec3 rhs)
{
	t_vec3	result;

	result.x = lhs.x * rhs.x;
	result.y = lhs.y * rhs.y;
	result.z = lhs.z * rhs.z;
	return (result);
}

t_vec3	div_vec(t_vec3 lhs, t_vec3 rhs)
{
	t_vec3	result;

	result.x = lhs.x / rhs.x;
	result.y = lhs.y / rhs.y;
	result.z = lhs.z / rhs.z;
	return (result);
}

t_vec3	scal_mul_vec(t_vec3 lhs, double rhs)
{
	t_vec3	result;

	result.x = lhs.x * rhs;
	result.y = lhs.y * rhs;
	result.z = lhs.z * rhs;
	return (result);
}

t_vec3	scal_div_vec(t_vec3 lhs, double rhs)
{
	t_vec3	result;

	result = scal_mul_vec(lhs, 1 / rhs);
	return (result);
}

double	length_vec(t_vec3 vec)
{
	return (sqrt(length_squared_vec(vec)));
}

double	length_squared_vec(t_vec3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

double	dot(t_vec3 lhs, t_vec3 rhs)
{
	return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
}

t_vec3	cross(t_vec3 lhs, t_vec3 rhs)
{
	return (construct_vec(
		lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x));
}

t_vec3 normalize(t_vec3 vec)
{
	return (scal_div_vec(vec, length_vec(vec)));
}

t_vec3	random_vec(double min, double max)
{
	return (construct_vec(random_double(min, max), random_double(min, max), random_double(min, max)));
}

t_vec3	random_in_unit_sphere(void)
{
	t_vec3	p;

	while (1)
	{
		p = random_vec(-1, 1);
		if (length_squared_vec(p) >= 1)
			continue ;
		return (p);
	}
}

t_vec3	random_unit_vector(void)
{
	double	a = random_double(0, 2 * M_PI);
	double	z = random_double(-1, 1);
	double	r = sqrt(1 - z * z);
	return (construct_vec(r * cos(a), r * sin(a), z));
}

t_vec3 reflect(t_vec3 v, t_vec3 n)
{
	return (sub_vec(v, scal_mul_vec(n, 2 * dot(v, n))));
}

t_color	construct_color(double e0, double e1, double e2)
{
	t_color	color;

	color.x = clamp(e0, 0, 1);
	color.y = clamp(e1, 0, 1);
	color.z = clamp(e2, 0, 1);
	return (color);
}

// #include <stdio.h>
// int	main()
// {
// 	t_vec3	a;
// 	t_vec3	b;
// 	t_vec3	c;

// 	construct_vec3_params(&a, 5.0, 5.0, 3.0);
// 	construct_vec3_params(&b, 2.0, 2.0, 0.0);
// 	construct_vec3_params(&c, 1.0, 0.0, 1.0);

// 	t_vec3 result = plus_vec(a, minus_vec(c.negative_vec(&c), b)); // result = a + (-c - b);
// 	printf("vector x: %f y: %f z: %f\n", result.x, result.y, result.z);
// }
