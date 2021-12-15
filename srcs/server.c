/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:12:39 by acousini          #+#    #+#             */
/*   Updated: 2021/12/15 12:48:07 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	handle_sigusr(int byte, int pid)
{
	static int	c = 0;
	static int	size = 0;

	c += byte << size;
	size++;
	if (c < 0 || c > 255)
	{
		c = 0;
		size = 0;
		write(1, "\nCommunication error\n", 22);
		kill(pid, SIGUSR2);
	}
	if (size == 7)
	{
		if (c == '\0')
		{
			ft_putstr_fd("\n", 1);
			kill(pid, SIGUSR2);
			size = 0;
			c = 0;
			return ;
		}
		else
			ft_putchar_fd(c, 1);
		size = 0;
		c = 0;
	}
	usleep(500);
	if (kill(pid, SIGUSR1) == -1)
	{
		printf("Problem with kill transmission. Abort. ERR_01\n");
		exit(EXIT_FAILURE);
	}
}

static void	handler(int signal, siginfo_t *info, void *context)
{
	static int	pid;
	
	if (info->si_pid != 0)
		pid = info->si_pid;
	(void)context;
	// if (info->si_pid == 0)
	// {
	// 	printf("info_pid == %d\n", info->si_pid);
	// 	printf("pid == %d\n", pid);
	// 	printf("MON PID EST EGAL A 0???\n");
	// }
	if (signal == SIGUSR1)
	{
		handle_sigusr(0, pid);
	}
	else if (signal == SIGUSR2)
	{
		handle_sigusr(1, pid);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sig;
	// sigset_t			block_mask;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("For correct behaviour, don't use any arguments\n", 1);
		return (0);
	}
	sigemptyset(&sig.sa_mask);
	// sigemptyset(&block_mask);
	// sigemptyset(&block_mask);
	// sigaddset(&block_mask, SIGUSR1);
	// sigaddset(&block_mask, SIGUSR2);
	// sig.sa_handler = 0;
	sig.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sig.sa_mask);
	// sig.sa_mask = block_mask;
	sig.sa_sigaction = handler;
	write(1, "pid = ", 7);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 2);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);

	// sig_info_t	
	while (1)
	{	
		// printf("toto\n");
		pause();
	}
	// ft_putstr_fd(g_input.message, 1);
	printf("JE NE SUIS PAS PROPRE\n");
	return (0);
}
