/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtod_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:10:41 by khanadat          #+#    #+#             */
/*   Updated: 2025/11/29 20:47:55 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strtod_utils.h"
#include "libft.h"

static int	get_frac(int range, const char **p, int *mantsize);

double	set_strtod(double fraction, char **endPtr, int sign, const char *p)
{
	if (endPtr)
		*endPtr = (char *)p;
	if (sign)
		return (-fraction);
	return (fraction);
}

void	set_fraction(t_strtod *tod)
{
	int	frac1;
	int	frac2;

	frac1 = get_frac(9, &tod->p, &tod->mantsize);
	frac2 = get_frac(0, &tod->p, &tod->mantsize);
	tod->fraction = (1.0e9 * frac1) + frac2;
}

static int	get_frac(int range, const char **p, int *mantsize)
{
	int				frac;
	register int	c;

	frac = 0;
	while (range < *mantsize)
	{
		c = *((*p)++);
		if (c == '.')
			c = *((*p)++);
		frac = 10 * frac + (c - '0');
		(*mantsize)--;
	}
	return (frac);
}
