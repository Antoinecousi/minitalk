/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 19:13:49 by acousini          #+#    #+#             */
/*   Updated: 2021/12/08 18:27:00 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	write_input(char *str, int pid)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		j = 0;
		printf("coucou on est ici\n");
		while (j <= 6)
		{
			if (str[i] >> j & 1)
			{
				if (kill(pid, SIGUSR2) == -1)
					exit(EXIT_FAILURE);
			}
			else
				if (kill(pid, SIGUSR1) == -1)
					exit(EXIT_FAILURE);
			j++;
			pause();
		}
		i++;
	}
}

void	handler(int signal)
{
	if (signal == SIGUSR1)
	{
		printf("");
	}
	if (signal == SIGUSR2)
	{
		printf("Signal error\n");
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	char				*str;
	struct sigaction	sig;

	sig.sa_flags = SA_RESTART;
	sig.sa_handler = handler;
	if (argc != 3)
	{
		ft_putstr_fd("Usage is : \t./client \"Server PID\" \"String\"", 1);
		return (0);
	}
	str = argv[2];
	usleep(1500);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	// signal(SIGUSR1, handler);
	// signal(SIGUSR2, handler);
	write_input(str, ft_atoi(argv[1]));
	return (0);
}
