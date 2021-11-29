/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:44:13 by acousini          #+#    #+#             */
/*   Updated: 2021/11/26 15:19:45 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t		i;
	t_list		*current;

	i = 0;
	current = lst;
	if (!lst)
		return (i);
	while (lst->next != NULL)
	{
		i++;
		lst = lst->next;
	}
	i++;
	return (i);
}
