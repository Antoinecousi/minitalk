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
		while (j <= 6)
		{
			if (str[i] >> j & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
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
		printf("COUCOU\n");
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
	usleep(100);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	write_input(str, ft_atoi(argv[1]));
	return (0);
}
