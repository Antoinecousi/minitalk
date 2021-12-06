/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:12:39 by acousini          #+#    #+#             */
/*   Updated: 2021/12/06 17:18:47 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static t_strct	g_input;

void	handle_sigusr1(int d)
{
	(void)d;
	g_input.size++;
	if (g_input.size >= 7)
	{
		ft_putchar_fd(g_input.c, 1);
		g_input.size = 0;
		g_input.c = 0;
	}
}

void	handle_sigusr2(int d)
{
	(void)d;
	g_input.c += 1 << g_input.size;
	g_input.size++;
	if (g_input.size >= 7)
	{
		ft_putchar_fd(g_input.c, 1);
		g_input.size = 0;
		g_input.c = 0;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 1)
	{
		ft_putstr_fd("For correct behaviour, don't use any arguments\n", 1);
		return (0);
	}
	(void)argv;
	write(1, "pid = ", 6);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	signal(SIGUSR1, handle_sigusr1);
	signal(SIGUSR2, handle_sigusr2);
	while (1)
		pause();
	return (0);
}
