/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtod_utils0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:24:58 by khanadat          #+#    #+#             */
/*   Updated: 2025/11/29 20:47:58 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strtod_utils.h"
#include "libft.h"
#include <math.h>

#define INF_LEN 8
#define NAN_LEN 3

static double	get_inf(const char *p, char **endptr, int sign);
static double	get_nan(const char *p, char **endptr, int sign);

char	*strtod_skip(const char *string, t_strtod *tod)
{
	while (ft_isspace(*string))
		string++;
	if (*string == '-' || *string == '+')
		tod->sign = (*(string++) == '-');
	return ((char *)string);
}

double	get_special(char **endptr, t_strtod *tod)
{
	double	special;

	special = get_inf(tod->p, endptr, tod->sign);
	if (special)
		return (special);
	special = get_nan(tod->p, endptr, tod->sign);
	if (special)
		return (special);
	return (EXIT_SUCCESS);
}

static double	get_inf(const char *p, char **endptr, int sign)
{
	static const char	*inf_str = "infinity";
	size_t				i;

	i = 0;
	while (i < INF_LEN && p[i])
	{
		if (ft_tolower(p[i]) != inf_str[i])
			break ;
		i++;
	}
	if (3 <= i)
	{
		if (endptr && i == INF_LEN)
			*endptr = (char *)(p + i);
		else if (endptr)
			*endptr = (char *)(p + 3);
		return ((1 - 2 * (sign)) * INFINITY);
	}
	return (EXIT_SUCCESS);
}

static double	get_nan(const char *p, char **endptr, int sign)
{
	static const char	*nan_str = "nan";
	size_t				i;

	i = 0;
	while (i < NAN_LEN && p[i])
	{
		if (ft_tolower(p[i]) != nan_str[i])
			break ;
		i++;
	}
	if (i == NAN_LEN)
	{
		if (endptr)
			*endptr = (char *)(p + i);
		return ((1 - 2 * (sign)) * NAN);
	}
	return (EXIT_SUCCESS);
}
