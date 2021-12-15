/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acousini <acousini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 19:13:49 by acousini          #+#    #+#             */
/*   Updated: 2021/12/15 17:18:24 by acousini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	error_handling(int pid)
{
	write(1, "ERROR\n", 6);
	(void)pid;
	exit(1);
}

void	write_input(char *str, int pid)
{
	size_t		i;
	int			j;

	i = 0;
	while (i <= ft_strlen(str))
	{
		j = 0;
		while (j <= 6)
		{
			usleep(1500);
			if (str[i] >> j & 1)
			{
				if (kill(pid, SIGUSR2) == -1)
					error_handling(pid);
			}
			else
				if (kill(pid, SIGUSR1) == -1)
					error_handling(pid);
			j++;
			pause();
		}
		i++;
	}
}

void	handler(int signal)
{
	if (signal == SIGUSR2)
	{
		write(1, "Transmission succeeded!\n", 24);
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
	usleep(10000);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	write_input(str, ft_atoi(argv[1]));
	return (0);
}
