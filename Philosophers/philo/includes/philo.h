/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:55:03 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/10 09:25:07 by yioffe           ###   ########.fr       */
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
    struct s_philo	*next;
	struct s_config *config;
}	t_philo;

int	atoi_positive(char *str);
void	*philosopher_routine(void *arg);
void pick_up_forks(t_philo *philo);
void put_down_forks(t_philo *philo);
long	current_time_in_ms(void);


# endif