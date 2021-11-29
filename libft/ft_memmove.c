/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:59:27 by acousini          #+#    #+#             */
/*   Updated: 2021/01/10 16:20:41 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	char				rev;
	unsigned char		*source;
	unsigned char		*dest;

	if (!dst && !src)
		return (NULL);
	rev = +1;
	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (dst > src)
	{
		rev = -1;
		source = (unsigned char *)(src + len - 1);
		dest = (unsigned char *)(dst + len - 1);
	}
	i = 0;
	while (i < len)
	{
		*dest = *source;
		dest += rev;
		source += rev;
		i++;
	}
	return (dst);
}
