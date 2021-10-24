/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 01:29:34 by sarchoi           #+#    #+#             */
/*   Updated: 2021/10/25 00:12:07 by sarchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_char_bits(int pid, char *c)
{
	int	i;

	i = 7;
	while (i--)
	{
		if ((*c & (1 << i)) == 0)
			send_0(pid);
		else
			send_1(pid);
		usleep(100);
	}
}

void	client(int pid, char *message)
{
	while (*message)
	{
		send_char_bits(pid, message);
		message++;
		usleep(10);
	}
	send_end_of_text(pid);
	ft_putstr_fd("Sent to ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd("\n", 1);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_putstr_fd("<usage> ", 1);
		ft_putstr_fd(argv[0], 1);
		ft_putstr_fd(" [server_pid] [message]\n", 1);
		return (EXIT_FAILURE);
	}
	client(ft_atoi(argv[1]), argv[2]);
	return (EXIT_SUCCESS);
}
