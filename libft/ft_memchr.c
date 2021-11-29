/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:05:18 by acousini          #+#    #+#             */
/*   Updated: 2021/11/26 15:27:52 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		chr;

	i = 0;
	chr = (unsigned char)c;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == chr)
			return (((unsigned char *)s) + i);
		i++;
	}
	return (NULL);
}
