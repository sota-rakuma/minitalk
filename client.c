/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 19:04:07 by srakuma           #+#    #+#             */
/*   Updated: 2021/07/24 22:21:22 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int sig)
{
	static int	bites;

	if (sig == SIGUSR1)
		bites++;
	else if (sig == SIGUSR2)
	{
		ft_putnbr_fd(bites, 1);
		write(1, "bites	sent\n", 12);
		exit(EXIT_SUCCESS);
	}
}

static int	send_signal(pid_t s_pid, char ch)
{
	int	cnt;

	cnt = 8;
	while (cnt-- > 0)
	{
		usleep(60);
		if (ch & (1 << cnt))
		{
			if (kill(s_pid, SIGUSR1) == -1)
				return (0);
		}
		else
		{
			if (kill(s_pid, SIGUSR2) == -1)
				return (0);
		}
	}
	return (1);
}

void	send_char(char **argv)
{
	pid_t	s_pid;

	s_pid = atopid(*argv);
	argv++;
	while (1)
	{
		if (**argv == '\0')
			**argv = '\x04';
		if (!send_signal(s_pid, **argv))
		{
			write(1, "kill func error\n", 16);
			exit(EXIT_FAILURE);
		}
		if (!sleep(2))
		{
			write (1, "didn't reach bit\n", 17);
			exit(EXIT_FAILURE);
		}
		(*argv)++;
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	act;

	act.sa_handler = signal_handler;
	arg_check(argc, ++argv);
	if (sigaction(SIGUSR1, &act, NULL) != 0
		|| sigaction(SIGUSR2, &act, NULL) != 0)
	{
		write(2, "sigaction error\n, errno is	", 16);
		ft_putnbr_fd(errno, 2);
		write(2, "\n", 1);
		exit(EXIT_FAILURE);
	}
	send_char(argv);
	return (0);
}
