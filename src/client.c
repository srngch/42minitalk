/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 01:29:34 by sarchoi           #+#    #+#             */
/*   Updated: 2021/10/22 04:02:14 by sarchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	client(int pid, char *message);

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

void	send_0(int pid)
{
	if (kill(pid, SIGUSR1) == FT_ERROR)
		ft_exit_failure_with_msg("Signal(SIGUSR1) transmission failed.");
}

void	send_1(int pid)
{
	if (kill(pid, SIGUSR2) == FT_ERROR)
		ft_exit_failure_with_msg("Signal(SIGUSR2) transmission failed.");
}

void	send_end_of_text(int pid)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		send_0(pid);
		i++;
		usleep(100);
	}
}

void	char_to_bits(int pid, char *c)
{
	int	i;

	i = 6;
	while (i >= 0)
	{
		if ((*c & (1 << i)) == 0)
			send_0(pid);
		else
			send_1(pid);
		usleep(100);
		i--;
	}
}

int	str_to_bits(int pid, char *message)
{
	char	*ptr_message;

	ptr_message = message;
	while (*ptr_message)
	{
		char_to_bits(pid, ptr_message);
		ptr_message++;
	}
	send_end_of_text(pid);
	return (FT_SUCCESS);
}

void	client(int pid, char *message)
{
	str_to_bits(pid, message);
	ft_putstr_fd("Sent to ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd("\n", 1);
}
