/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srakuma <srakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 19:04:30 by srakuma           #+#    #+#             */
/*   Updated: 2021/07/24 22:21:03 by srakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <stdio.h>
# include <sys/types.h>
# include <stdint.h>
# include <limits.h>
# include <errno.h>

int		ft_count_digit(int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	arg_check(int argc, char **argv);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *s);
pid_t	atopid(char *str);
void	*ft_memset(void *b, int c, size_t len);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef SIGUSR1
#  define SIGUSR1 1
# endif

# ifndef SIGUSR2
#  define SIGUSR2 0
# endif

#endif