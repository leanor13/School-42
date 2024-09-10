/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:55:03 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/10 14:46:00 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/time.h>

# define NEG_ERROR -1

struct s_philo;

typedef struct s_config
{
	int number_of_philosophers;
    int	time_to_die;
    int	time_to_eat;
    int	time_to_sleep;
    int	number_of_times_each_philosopher_must_eat;
	bool	stop;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_write;
    pthread_mutex_t	mutex_stop;
	struct s_philo	*first_philo;
}	t_config;

typedef struct s_philo
{
    int				id;
    int				eat_num;
    bool			alive;
    pthread_mutex_t	mutex_eating;
    struct timeval	last_eat_time;
    int				eat_count;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *mutex_alive;
    struct s_philo	*next;
	struct s_config *config;
}	t_philo;

int	atoi_positive(char *str);
void	*philosopher_routine(void *arg);
void *monitor_routine(void *params);
void pick_up_forks(t_philo *philo);
void put_down_forks(t_philo *philo);
long	current_time_in_ms(void);
long time_diff_in_ms(struct timeval start, struct timeval end);
void	ft_putnbr_fd(unsigned long long n, int fd);


t_philo	*initiate_philos(t_config *config);
t_config	*init_config(int argc, char **argv);
int	create_threads(pthread_t **threads, t_philo *philos, t_config *config);

void	free_philos(t_philo *philos);
void cleanup(t_philo *philos, pthread_t *threads, t_config *config);


# endif