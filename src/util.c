/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 01:29:47 by sarchoi           #+#    #+#             */
/*   Updated: 2021/11/05 21:43:10 by sarchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_exit_failure_with_msg(char *message)
{
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd("<ERROR> ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	exit(EXIT_FAILURE);
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

	i = 7;
	while (i--)
	{
		send_0(pid);
		usleep(50);
	}
}
