/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 01:29:32 by sarchoi           #+#    #+#             */
/*   Updated: 2021/10/17 03:10:16 by sarchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <time.h> // TEST

int	print_pid(void)
{
	char	*pid;

	pid = ft_itoa(getpid());
	if (pid == FT_NULL)
		return (FT_ERROR);
	ft_putstr_fd("Server PID: ", STDIN_FILENO);
	ft_putstr_fd(pid, STDIN_FILENO);
	ft_putstr_fd("\n", STDIN_FILENO);
	free(pid);
	return (FT_SUCCESS);
}

void	handler(int signo, siginfo_t* info, void * uap)
{
	(void)info;
	(void)uap;
	if (signo == SIGUSR1)
	{
		ft_putstr_fd("0", 1);
	}
	else if (signo == SIGUSR2)
	{
		ft_putstr_fd("1", 1);
	}
}

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

int	main(void)
{
	if (print_pid() == FT_ERROR)
		ft_exit_failure_with_msg("memory for pid not allocated.");
	server();
	while (FT_TRUE)
		;
	return (EXIT_SUCCESS);
}
