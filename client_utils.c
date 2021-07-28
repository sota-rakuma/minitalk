/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 16:52:16 by srakuma           #+#    #+#             */
/*   Updated: 2021/07/24 21:12:10 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

pid_t	atopid(char *str)
{
	pid_t	pid;

	pid = 0;
	while (*str)
	{
		pid = (10 * pid) + (*str - '0');
		str++;
	}
	return (pid);
}

static int	is_ok(int num, int c)
{
	int	ov_div;
	int	ov_mod;
	int	nxt;

	nxt = c - '0';
	ov_div = INT_MAX / 10;
	ov_mod = INT_MAX % 10;
	if ((ov_div < num) || (ov_div == num && ov_mod < nxt))
		return (0);
	return (1);
}

void	arg_check(int argc, char **argv)
{
	int	num;
	int	i;

	if (argc != 3)
	{
		write(2, "The number of arguments is wrong\n", 34);
		exit (EXIT_FAILURE);
	}
	num = 0;
	i = 0;
	while (*(*argv + i))
	{
		if (!('0' <= *(*argv + i) && *(*argv + i) <= '9')
			|| !is_ok(num, *(*argv + i)) || **argv == '0')
		{
			write(2, "input right params\n", 20);
			exit(EXIT_FAILURE);
		}
		num = num * 10 + (*(*argv + i) - '0');
		i++;
	}
}
