#include "vec3.h"
#include "rt_utils.h"

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

t_vec3	random_cosine_direction(void)
{
	t_vec3	result;
	double	u1 = random_double(0, 1);
	double	u2 = random_double(0, 1);

	result.x = cos(2 * M_PI * u1) * sqrt(u2);
	result.y = sin(2 * M_PI * u1) * sqrt(u2);
	result.z = sqrt(1 - u2);
	return (result);
}

t_vec3	random_in_unit_disk(void)
{
	while (1)
	{
		t_vec3	p = construct_vec(random_double(-1, 1), random_double(-1, 1), 0);
		if (length_squared_vec(p) >= 1)
			continue ;
		return (p);
	}
}

void	build_onb(t_vec3 onb[3], t_vec3 n)
{
	onb[2] = normalize(n);
	t_vec3	a = (fabs((onb[2]).x) > 0.9) ? construct_vec(0, 1, 0) : construct_vec(1, 0, 0);
	onb[1] = normalize(cross(onb[2], a));
	onb[0] = cross(onb[2], onb[1]);
	return ;
}

t_vec3	local_onb(t_vec3 onb[3], t_vec3 a) // a = random_cosvec()
{
	return (add_vec(scal_mul_vec(onb[0], a.x), add_vec(scal_mul_vec(onb[1], a.y), scal_mul_vec(onb[2], a.z))));
	// x * u + y * v + z * w
}

t_vec3 reflect(t_vec3 v, t_vec3 n)
{
	return (sub_vec(v, scal_mul_vec(n, 2 * dot(v, n))));
}

t_vec3	refract(t_vec3 uv, t_vec3 n, double refractive_ratio)
{
	double	cos_theta = dot(negative_vec(uv), n);
	t_vec3	r_out_parallel = scal_mul_vec(add_vec(uv, scal_mul_vec(n, cos_theta)), refractive_ratio);
	t_vec3	r_out_perp = scal_mul_vec(n, -sqrt(1.0 - length_squared_vec(r_out_parallel)));
	return (add_vec(r_out_parallel, r_out_perp));
}

t_color	construct_color(double e0, double e1, double e2)
{
	t_color	color;

	color.x = clamp(e0 / 255, 0, 1);
	color.y = clamp(e1 / 255, 0, 1);
	color.z = clamp(e2 / 255, 0, 1);
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
