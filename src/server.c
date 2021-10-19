/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 01:29:32 by sarchoi           #+#    #+#             */
/*   Updated: 2021/10/20 03:41:40 by sarchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <time.h> // TEST

void	print_pid(void)
{
	ft_putstr_fd("Server PID: ", STDIN_FILENO);
	ft_putnbr_fd(getpid(), STDIN_FILENO);
	ft_putstr_fd("\n", STDIN_FILENO);
}

void	char_to_bits(char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((c & (1 << i)) == 0)
			ft_putchar_fd('0', 1);
		else
			ft_putchar_fd('1', 1);
		usleep(100);
		i--;
	}
}

void	handler(int signo, siginfo_t* info, void * uap)
{
	static char				buf[100];
	static int				buf_index = 0;
	static unsigned char	c = 0;
	static int				bit_index = 0;

	(void)info;
	(void)uap;
	if (buf_index == 0)
		ft_memset(buf, 0, 100);
	c |= (signo == SIGUSR2);
	if (c == 127 || buf_index == 99)
	{
		ft_putstr_fd(buf, 1);
		ft_memset(buf, '\0', 99);
		buf_index = 0;
		bit_index = 0;
		if (c == 127)
		{
			ft_putstr_fd("\n", 1);
			c = 0;
			return ;
		}
		c = 0;
	}
	if (bit_index == 6)
	{
		buf[buf_index++] = c;
		c = 0;
		bit_index = 0;
		return ;
	}
	bit_index++;
	c <<= 1;
}

/*
 * signals
 * - SIGUSR1: 0
 * - SIGUSR2: 1
 */
void	server(void)
{
	struct sigaction	sigusr1;
	struct sigaction	sigusr2;

	sigusr1.sa_sigaction = handler;
	sigemptyset(&sigusr1.sa_mask);
	sigusr1.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sigusr1, NULL) == FT_ERROR)
		ft_exit_failure_with_msg("signal(SIGUSR1) error");
	sigusr2.sa_sigaction = handler;
	sigemptyset(&sigusr2.sa_mask);
	sigusr2.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR2, &sigusr2, NULL) == FT_ERROR)
		ft_exit_failure_with_msg("signal(SIGUSR2) error");
}

int	main(int argc, char **argv)
{
	if (argc != 1)
	{
		ft_putstr_fd("<usage> ", 1);
		ft_putstr_fd(argv[0], 1);
		ft_putstr_fd("\n", 1);
		return (EXIT_FAILURE);
	}
	print_pid();
	server();
	while (FT_TRUE)
		;
	return (EXIT_SUCCESS);
}
