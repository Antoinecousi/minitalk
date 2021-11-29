/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 19:13:49 by acousini          #+#    #+#             */
/*   Updated: 2021/11/29 20:03:36 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int	main(int argc, char **argv)
{
	char	*str;

	if (argc != 3)
	{
		ft_putstr_fd("usage is ./client \"serverpid\" \"string\"");
		return (0);
	}
	str = argv[2];
	write_input(str, ft_atoi(argv[1]));
	return (0);
}