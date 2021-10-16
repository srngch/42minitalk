/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 01:29:34 by sarchoi           #+#    #+#             */
/*   Updated: 2021/10/17 03:42:19 by sarchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	client(int pid, char *message);

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_putstr_fd("<usage> ./", 1);
		ft_putstr_fd(argv[0], 1);
		ft_putstr_fd(" [server_pid] [message]\n", 1);
		return (EXIT_FAILURE);
	}
	client(ft_atoi(argv[1]), argv[2]);
	return (EXIT_SUCCESS);
}

int	send_0(int pid)
{
	if (kill(pid, SIGUSR1) == FT_ERROR)
		ft_exit_failure_with_msg("Signal(SIGUSR1) transmission failed.");
	return (FT_SUCCESS);
}

int	send_1(int pid)
{
	if (kill(pid, SIGUSR2) == FT_ERROR)
		ft_exit_failure_with_msg("Signal(SIGUSR2) transmission failed.");
	return (FT_SUCCESS);
}

void	char_to_bits(int pid, char *c)
{
	unsigned char	flag;
	int				i;

	i = 7;
	while (i >= 0)
	{
		flag = (unsigned char) (*c & (1 << i));
		if (flag == 0)
		{
			send_0(pid);
			// printf("0 "); // TEST
		}
		else
		{
			send_1(pid);
			// printf("1 "); // TEST
		}
		usleep(500);
		i--;
	}
}

int	str_to_bits(int pid, char *message)
{
	char	*ptr_message;

	ptr_message = message;
	while (*ptr_message)
	{
		// printf("message char: %c(%d)\t", *ptr_message, *ptr_message); // TEST
		char_to_bits(pid, ptr_message);
		// printf("\n"); //TEST
		ptr_message++;
	}
	return (1);
}

void	client(int pid, char *message)
{
	str_to_bits(pid, message);
	printf("Sent signal to %d\n", pid);
	usleep(500);
}
