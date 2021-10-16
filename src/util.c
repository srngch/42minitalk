/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 01:29:47 by sarchoi           #+#    #+#             */
/*   Updated: 2021/10/17 02:03:30 by sarchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void ft_exit_failure_with_msg(char *message)
{
	ft_putstr_fd(RED, STDIN_FILENO);
	ft_putstr_fd("<ERROR> ", STDIN_FILENO);
	ft_putstr_fd(message, STDIN_FILENO);
	ft_putstr_fd("\n", STDIN_FILENO);
	ft_putstr_fd(RESET, STDIN_FILENO);
	exit(EXIT_FAILURE);
}
