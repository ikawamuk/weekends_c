/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sun_system_strtod.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:19:38 by khanadat          #+#    #+#             */
/*   Updated: 2025/11/29 20:30:35 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "strtod_utils.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

static void	count_mantsize(t_strtod *tod);
static void	set_fracexp(t_strtod *tod);
static void	set_exp(t_strtod *tod);
static void	mul_fraction(t_strtod *tod);

double	ft_strtod(const char *string, char **endPtr)
{
	t_strtod	tod;

	ft_bzero(&tod, sizeof(t_strtod));
	tod.p = strtod_skip(string, &tod);
	tod.fraction = get_special(endPtr, &tod);
	if (tod.fraction)
		return (tod.fraction);
	count_mantsize(&tod);
	tod.pexp = tod.p;
	tod.p -= tod.mantsize;
	set_fracexp(&tod);
	if (tod.mantsize == 0)
		return (set_strtod(0.0, endPtr, FALSE, (char *)string));
	set_fraction(&tod);
	tod.p = tod.pexp;
	set_exp(&tod);
	mul_fraction(&tod);
	return (set_strtod(tod.fraction, endPtr, tod.sign, tod.p));
}

static void	count_mantsize(t_strtod *tod)
{
	tod->decpt = -1;
	while (1)
	{
		if (!ft_isdigit(*(tod->p)))
		{
			if (*(tod->p) != '.' || 0 <= tod->decpt)
				break ;
			tod->decpt = tod->mantsize;
		}
		(tod->p)++;
		(tod->mantsize)++;
	}
}

static void	set_fracexp(t_strtod *tod)
{
	if (tod->decpt < 0)
		tod->decpt = tod->mantsize;
	else
		(tod->mantsize)--;
	if (18 < tod->mantsize)
	{
		tod->mantsize = 18;
		tod->fracexp = tod->decpt - 18;
	}
	tod->fracexp = tod->decpt - tod->mantsize;
}

static void	set_exp(t_strtod *tod)
{
	tod->expsign = FALSE;
	if ((*(tod->p) == 'E') || (*(tod->p) == 'e'))
	{
		(tod->p)++;
		if (*(tod->p) == '-' || *(tod->p) == '+')
			tod->expsign = (*(tod->p)++ == '-');
		while (ft_isdigit(*(tod->p)))
			tod->exp = tod->exp * 10 + (*(tod->p)++ - '0');
	}
	if (tod->expsign)
		tod->exp = tod->fracexp - tod->exp;
	else
		tod->exp = tod->fracexp + tod->exp;
	if (tod->exp < 0)
		tod->expsign = TRUE;
	else
		tod->expsign = FALSE;
	tod->exp = ft_abs(tod->exp);
	if (MAX_EXPONENT < tod->exp)
		tod->exp = MAX_EXPONENT;
}

static void	mul_fraction(t_strtod *tod)
{
	double			*d;
	double			dblexp;
	static double	powers0f10[] = {\
10., 100., 1.0e4, 1.0e8, 1.0e16, \
1.0e32, 1.0e64, 1.0e128, 1.0e256
	};

	dblexp = 1.0;
	d = powers0f10;
	while (tod->exp != 0)
	{
		if (tod->exp & 01)
			dblexp *= *d;
		tod->exp >>= 1;
		d += 1;
	}
	if (tod->expsign)
		tod->fraction /= dblexp;
	else
		tod->fraction *= dblexp;
}

// #include <stdlib.h>
// #include <stdio.h>

// void	print_specified_bytes_as_binary
// (unsigned char byte, int start, int end) {
// 	if (start < end || 7 < start || end < 0)
// 		return ;
// 	for (int bit = start; bit >= end; bit--) {
// 		if (byte & (1 << bit))
// 			write(1, "1", 1);
// 		else
// 			write(1, "0", 1);
// 	}
// }

// void	print_bytes_as_binary(unsigned char byte) {
// 	print_specified_bytes_as_binary(byte, 7, 0);
// }

// void	print_double_bits(void *ptr) {
// 	unsigned char	*bytes = (unsigned char *)ptr;
// 	size_t			i;

// 	i = 8;
// 	while (i != 0) {
// 		--i;
// 		if (i == 7) {
// 			print_specified_bytes_as_binary(bytes[i], 7, 7);
// 			write(1, ", ", 2);
// 			print_specified_bytes_as_binary(bytes[i], 6, 0);
// 		}
// 		else if (i == 6) {
// 			print_specified_bytes_as_binary(bytes[i], 7, 4);
// 			write(1, ", ", 2);
// 			print_specified_bytes_as_binary(bytes[i], 3, 0);
// 		}
// 		else
// 			print_bytes_as_binary(bytes[i]);
// 		if (i != 0 && i != 7)
// 			write(1, ", ", 2);
// 	}
// 	write(1, "\n", 1);
// }

// int	main(int argc, char *argv[])
// {
// 	double	tmp;
// 	char	*ptr;

// 	if (argc == 1)
// 		return 1;
// 	tmp = ft_strtod(argv[1], &ptr);
// 	printf("ft\t: %f\n", tmp);
// 	printf("ft\t: %s\n", ptr);
// 	print_double_bits(&tmp);
// 	tmp = strtod(argv[1], &ptr);
// 	printf("real\t: %f\n", tmp);
// 	printf("real\t: %s\n", ptr);
// 	print_double_bits(&tmp);
// 	printf("argv\t: %s\n", argv[1]);
// 	return 0;
// }
