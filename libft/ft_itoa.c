/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 17:21:11 by acousini          #+#    #+#             */
/*   Updated: 2021/11/26 15:17:44 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getsize(int n)
{
	int				count;
	unsigned int	copy;

	count = 1;
	if (n < 0)
	{
		count++;
		copy = (-1 * n);
	}
	else
		copy = n;
	while (copy > 9)
	{
		copy = copy / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	unsigned int	copy;
	int				i;
	char			*itoa;

	i = ft_getsize(n);
	itoa = (char *)malloc(i + 1);
	if (!itoa)
		return (NULL);
	if (n < 0)
	{
		itoa[0] = '-';
		copy = (-1 * n);
	}
	else
		copy = n;
	itoa[i--] = '\0';
	if (copy == 0)
		itoa[0] = '0';
	while (copy != 0)
	{
		itoa[i--] = (copy % 10) + 48;
		copy /= 10;
	}
	return (itoa);
}
