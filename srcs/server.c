/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:12:39 by acousini          #+#    #+#             */
/*   Updated: 2021/12/08 18:27:49 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static t_strct	g_input;

void	handle_sigusr1(int pid)
{
	g_input.size++;
	if (g_input.c < 0 || g_input.c > 255)
	{
		g_input.c = 0;
		g_input.size = 0;
		write(1, "\nCommunication error\n", 21);
		kill(pid, SIGUSR2);
	}
	if (g_input.size >= 7)
	{
		ft_putchar_fd(g_input.c, 1);
		g_input.size = 0;
		g_input.c = 0;
	}
	// usleep(50);
	kill(pid, SIGUSR1);
}

void	handle_sigusr2(int pid)
{
	g_input.c += 1 << g_input.size;
	g_input.size++;
	if (g_input.c < 0 || g_input.c > 255)
	{
		g_input.c = 0;
		g_input.size = 0;
		write(1, "\nCommunication error\n", 21);
		kill(pid, SIGUSR2);
	}
	if (g_input.size >= 7)
	{
		ft_putchar_fd(g_input.c, 1);
		g_input.size = 0;
		g_input.c = 0;
	}
	// usleep(50);
	kill(pid, SIGUSR1);
}

static void	handler(int signal, siginfo_t *info, void *context)
{
	(void)context;
	if (signal == SIGUSR1)
		handle_sigusr1(info->si_pid);
	else if (signal == SIGUSR2)
		handle_sigusr2(info->si_pid);
}

int	main(int argc, char **argv)
{
	struct sigaction	sig;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("For correct behaviour, don't use any arguments\n", 1);
		return (0);
	}
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sig.sa_mask);
	sig.sa_sigaction = handler;
	write(1, "pid = ", 6);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
		pause();
	return (0);
}
