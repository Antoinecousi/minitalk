/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:12:39 by acousini          #+#    #+#             */
/*   Updated: 2021/12/10 18:22:21 by acousini         ###   ########.fr       */
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
			return ;
		}
		else
			ft_putchar_fd(c, 1);
		size = 0;
		c = 0;
	}
	usleep(200);
	if (kill(pid, SIGUSR1) == -1)
	{
		printf("Problem with kill transmission. Abort. ERR_01\n");
		exit(EXIT_FAILURE);
	}
}

static void	handler(int signal, siginfo_t *info, void *context)
{
	(void)context;
	// printf("%d\n", i);
	// printf("pid == %d\n", info->si_pid);
	if (info->si_pid == 0)
	{
		printf("MON PID EST EGAL A 0???\n");
		// return ;
	}
	if (signal == SIGUSR1)
	{
		handle_sigusr(0, info->si_pid);
	}
	else if (signal == SIGUSR2)
	{
		handle_sigusr(1, info->si_pid);
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
