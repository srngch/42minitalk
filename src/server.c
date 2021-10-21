/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 01:29:32 by sarchoi           #+#    #+#             */
/*   Updated: 2021/10/22 03:45:25 by sarchoi          ###   ########.fr       */
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

// void	clear_handler(char *buf, int *buf_index, unsigned char *c, int *bit_index)
// {
// 	ft_putstr_fd(buf, 1);
// 	ft_memset(buf, '\0', BUFFER_SIZE);
// 	*buf_index = 0;
// 	*bit_index = 0;
// 	if (*c == END_OF_TEXT)
// 	{
// 		ft_putstr_fd("\n", 1);
// 		*c = 0;
// 		return ;
// 	}
// 	*c = 0;
// }

void	*s_memset(void *b, int c, size_t len)
{
	unsigned char	*s;

	s = b;
	while (len-- > -1)
	{
		s[len] = (unsigned char)c;
	}
	return (b);
}

void	handler(int signo, siginfo_t* info, void * uap)
{
	static char	buf[BUFFER_SIZE];
	static int	buf_index;
	static int	bit_index;

	(void)info;
	(void)uap;
	if (buf_index == 0 && bit_index == 0)
		s_memset(buf, 0, BUFFER_SIZE);
	buf[buf_index] |= (signo == SIGUSR2);
	if (bit_index == 6)
	{
		bit_index = 0;
		if (buf[buf_index] == END_OF_TEXT)
		{
			buf_index = 0;
			ft_putstr_fd(buf, 1);
			ft_putstr_fd("\n", 1);
			return ;
		}
		if (buf_index == BUFFER_SIZE - 1)
		{
			buf_index = 0;
			ft_putstr_fd(buf, 1);
			return ;
		}
		buf_index++;
		return ;
	}
	bit_index++;
	buf[buf_index] <<= 1;
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
		pause();
	return (EXIT_SUCCESS);
}
