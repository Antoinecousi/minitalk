/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 17:08:17 by acousini          #+#    #+#             */
/*   Updated: 2021/11/26 15:21:14 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_occur(char str, char charset)
{
	if (str == charset)
		return (1);
	return (0);
}

static int	ft_get_size(const char *str, char charset)
{
	int		size;

	size = 0;
	while (*str)
	{
		if (ft_occur(*str, charset) == 0)
		{
			size++;
			while (*str && ft_occur(*str, charset) == 0)
				str++;
		}
		if (*str)
			str++;
	}
	return (size);
}

static void	ft_strcpy22(char *dst, const char *copy, const char *until)
{
	while (copy < until)
		*(dst++) = *(copy++);
	*dst = '\0';
}

char	**ft_split(char const *s, char c)
{
	char		**copy;
	int			i;
	const char	*from;
	int			j;

	j = 0;
	i = 0;
	copy = malloc(sizeof(char *) * (ft_get_size(s, c) + 1));
	if (!s || !copy)
		return (0);
	while (s[i])
	{
		if (ft_occur(s[i], c) == 0)
		{
			from = s + i;
			while (s[i] && ft_occur(s[i], c) == 0)
				i++;
			copy[j] = malloc(sizeof(char) * (s + i - from + 1));
			ft_strcpy22(copy[j++], from, s + i);
		}
		if (s[i])
			i++;
	}
	copy[j] = 0;
	return (copy);
}
