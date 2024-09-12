/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:03:23 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/12 14:16:48 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	atoi_positive(char *str)
{
	int	number;

	if (!str || !*str)
		return (NEG_ERROR);
	while (*str == 32 || (*str > 8 && *str < 14))
		str++;
	number = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (number > (INT_MAX - (*str - '0')) / 10)
			return (NEG_ERROR);
		number = 10 * number + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (NEG_ERROR);
	return (number);
}

void	ft_putnbr_fd(unsigned long long n, int fd)
{
	char	c;

	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	c = (n % 10) + '0';
	write(fd, &c, 1);
}

long	time_diff_in_ms(struct timeval start, struct timeval end)
{
	long	sec_diff;
	long	usec_diff;

	sec_diff = (end.tv_sec - start.tv_sec) * 1000;
	usec_diff = (end.tv_usec - start.tv_usec) / 1000;
	return (sec_diff + usec_diff);
}

long	current_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	philo_print(const char *message, t_philo *philo)
{
	t_config			*config;
	struct timeval		current_time;
	unsigned long long	timestamp_in_ms;

	config = philo->config;
	gettimeofday(&current_time, NULL);
	timestamp_in_ms = (current_time.tv_sec * 1000) + (current_time.tv_usec
			/ 1000);
	pthread_mutex_lock(&config->mutex_write);
	ft_putnbr_fd(timestamp_in_ms, STDOUT_FILENO);
	write(STDOUT_FILENO, " ", 1);
	ft_putnbr_fd(philo->id, STDOUT_FILENO);
	write(STDOUT_FILENO, " ", 1);
	while (*message)
	{
		write(STDOUT_FILENO, message, 1);
		message++;
	}
	write(STDOUT_FILENO, "\n", 1);
	pthread_mutex_unlock(&config->mutex_write);
}
