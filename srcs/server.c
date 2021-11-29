/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:12:39 by acousini          #+#    #+#             */
/*   Updated: 2021/11/29 19:49:39 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int	main(int argc, char **argv)
{
	if (argc != 1)
	{
		ft_putstr_fd("pryot", 1);
		return (0);
	}
	(void)argv;
	write(1, "pid = ", 6);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	signal(SIGUSR1, sigurs1);
	signal(SIGUSR2, sigurs2);
	return(0);
}