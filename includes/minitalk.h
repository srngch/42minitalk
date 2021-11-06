/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 23:46:05 by sarchoi           #+#    #+#             */
/*   Updated: 2021/11/06 17:50:06 by sarchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

# include "libft.h"

# define FT_SUCCESS		1
# define FT_ERROR		-1
# define FT_EOF			0

typedef int	t_bool;
# define FT_TRUE		1
# define FT_FALSE		0

/*
** ANSI Color Codes for terminal messages
*/
# define RED			"\x1b[31m"
# define GREEN			"\x1b[32m"
# define BLUE			"\x1b[34m"
# define YELLOW			"\x1b[33m"
# define MAGENTA		"\x1b[35m"
# define CYAN			"\x1b[36m"
# define RESET			"\x1b[0m"

void	ft_exit_failure_with_msg(char *message);
void	send_0(int pid);
void	send_1(int pid);

#endif
