/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 08:26:05 by khanadat          #+#    #+#             */
/*   Updated: 2026/01/03 13:20:37 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"



char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	printf("HERE1\n");
	printf("s: %s", s);
	printf("HERE2\n");
	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	return (ft_memmove(dup, s, len + 1));
}
