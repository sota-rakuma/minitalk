/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 19:55:27 by srakuma           #+#    #+#             */
/*   Updated: 2021/07/25 03:35:26 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	send_signal(pid_t c_pid, int sig)
{
	usleep(45);
	return (kill(c_pid, sig));
}

void	proc_of_a_bite(char ch, pid_t c_pid, char *buff, int bites)
{
	if (ch == 0x04)
	{
		--bites;
		send_signal(c_pid, SIGUSR2);
		write(1, buff, bites % BUFFER_SIZE);
		write(1, "\n", 1);
		ft_memset(buff, '\0', bites % BUFFER_SIZE);
		return ;
	}
	if (bites % BUFFER_SIZE == 0)
	{
		buff[BUFFER_SIZE - 1] = ch;
		write(1, buff, BUFFER_SIZE);
		ft_memset(buff, '\0', BUFFER_SIZE);
	}
	else
		buff[bites % BUFFER_SIZE - 1] = ch;
	send_signal(c_pid, SIGUSR1);
}

void	signal_action(int sig, siginfo_t *info, void *c)
{
	static char	buff[BUFFER_SIZE];
	static char	ch;
	static int	cnt;

	(void)c;
	if (sig == SIGUSR1)
		ch = (ch << 1) + 1;
	else
		ch <<= 1;
	cnt++;
	if (cnt % CHAR_BIT == 0)
	{
		proc_of_a_bite(ch, info->si_pid, buff, cnt / CHAR_BIT);
		if (ch == 0x04)
			cnt = 0;
		ch = 0;
	}
}

void	output_pid(pid_t pid)
{
	write(1, "server pid : ", 14);
	ft_putnbr_fd((int)pid, 1);
	write(1, "\n", 1);
}

int	main(void)
{
	struct sigaction	act;

	act.sa_flags = SA_SIGINFO | SA_RESTART;
	act.sa_sigaction = signal_action;
	output_pid(getpid());
	if (sigaction(SIGUSR1, &act, NULL) != 0
		|| sigaction(SIGUSR2, &act, NULL) != 0)
	{
		write(2, "sigaction error\n, errno is	", 16);
		ft_putnbr_fd(errno, 2);
		write(2, "\n", 1);
		exit(EXIT_FAILURE);
	}
	while (1)
		pause();
	return (0);
}
