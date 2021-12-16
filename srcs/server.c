/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:12:39 by acousini          #+#    #+#             */
/*   Updated: 2021/12/15 17:56:24 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int	error_handler(int pid)
{
	(void)pid;
	write(1, "\nProblem with kill transmission\n", 32);
	return (1);
}

void	handle_sigusr(int byte, int pid)
{
	static int	c = 0;
	static int	size = 0;

	c += byte << size;
	size++;
	if (size == 7)
	{
		if (c == '\0')
		{
			size = 0;
			c = 0;
			kill(pid, SIGUSR2);
			return ;
		}
		else
			write(1, &c, 1);
		size = 0;
		c = 0;
	}
	usleep(1500);
	if (kill(pid, SIGUSR1) != 0)
		exit(error_handler(pid));
}

static void	handler(int signal, siginfo_t *info, void *context)
{
	static int	pid = 0;

	if (info->si_pid != 0)
		pid = info->si_pid;
	(void)context;
	if (signal == SIGUSR1)
		handle_sigusr(0, pid);
	else if (signal == SIGUSR2)
		handle_sigusr(1, pid);
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
	sig.sa_flags = SA_SIGINFO | SA_RESTART;
	sig.sa_sigaction = handler;
	sigemptyset(&sig.sa_mask);
	write(1, "pid = ", 6);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
		pause();
	return (0);
}
