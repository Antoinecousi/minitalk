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
static int i = 0;

// void	error_signal(void int)
// {
// }

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
		// g_input.message[g_input.i++] = g_input.c;
		ft_putchar_fd(g_input.c, 1);
		g_input.size = 0;
		g_input.c = 0;
	}
	usleep(100);
	if (kill(pid, SIGUSR1) == -1)
		exit(EXIT_FAILURE);
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
		// g_input.message[g_input.i++] = g_input.c;
		ft_putchar_fd(g_input.c, 1);
		g_input.size = 0;
		g_input.c = 0;
	}
	usleep(100);
	if (kill(pid, SIGUSR1) == -1)
		exit(EXIT_FAILURE);
}

static void	handler(int signal, siginfo_t *info, void *context)
{
	(void)context;
	i++;
	printf("%d\n", i);
	printf("pid == %d\n", info->si_pid);
	if (info->si_pid == 0)
	{
		printf("ERROR gestion");
		exit(1);
	}
	if (signal == SIGUSR1)
	{
		handle_sigusr1(info->si_pid);
	}
	else if (signal == SIGUSR2)
		handle_sigusr2(info->si_pid);
}

int	main(int argc, char **argv)
{
	struct sigaction	sig;
	sigset_t			block_mask;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("For correct behaviour, don't use any arguments\n", 1);
		return (0);
	}
	sigemptyset(&sig.sa_mask);
	sigemptyset(&block_mask);
	// sigemptyset(&block_mask);
	sigaddset(&block_mask, SIGUSR1);
	sigaddset(&block_mask, SIGUSR2);
	// sig.sa_handler = 0;
	sig.sa_flags = SA_SIGINFO | SA_RESTART;
	// sigemptyset(&sig.sa_mask);
	sig.sa_mask = block_mask;
	sig.sa_sigaction = handler;
	write(1, "pid = ", 6);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
	{
		printf("toto\n");
		pause();
	}
	// ft_putstr_fd(g_input.message, 1);
	return (0);
}
