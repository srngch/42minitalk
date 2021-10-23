/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 01:29:32 by sarchoi           #+#    #+#             */
/*   Updated: 2021/10/24 01:56:48 by sarchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int signo, siginfo_t *info, void *uap)
{
	static unsigned char	c;
	static int				bit_index;

	(void)info;
	(void)uap;
	c |= (signo == SIGUSR2);
	if (bit_index++ == 6)
	{
		write(STDOUT_FILENO, &c, 1);
		c = 0;
		bit_index = 0;
		return ;
	}
	c <<= 1;
}

/*
** signals
** - SIGUSR1: receive 0
** - SIGUSR2: receive 1
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

void	print_pid(void)
{
	ft_putstr_fd("Server PID: ", STDOUT_FILENO);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
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
