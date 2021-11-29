/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:19:25 by acousini          #+#    #+#             */
/*   Updated: 2021/01/10 16:48:16 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		a;

	a = ft_strlen(s);
	while (a >= 0)
	{
		if (s[a] == c)
			return ((char *)s + a);
		a--;
	}
	return (NULL);
}
