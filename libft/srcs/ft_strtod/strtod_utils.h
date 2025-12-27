/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtod_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:24:53 by khanadat          #+#    #+#             */
/*   Updated: 2025/11/29 20:48:15 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRTOD_UTILS_H
# define STRTOD_UTILS_H

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

# ifndef MAX_EXPONENT
#  define MAX_EXPONENT 511
# endif

typedef struct s_strtod
{
	int			sign;
	int			expsign;
	double		fraction;
	const char	*p;
	const char	*pexp;
	int			exp;
	int			fracexp;
	int			mantsize;
	int			decpt;
}	t_strtod;

// 0
char	*strtod_skip(const char *string, t_strtod *tod);
double	get_special(char **endptr, t_strtod *tod);

// 1
double	set_strtod(double fraction, char **endPtr, int sign, const char *p);
void	set_fraction(t_strtod *tod);

#endif