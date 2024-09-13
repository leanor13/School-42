/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:55:03 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/13 10:46:17 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define NEG_ERROR -1

# define WRONG_INPUT "Usage: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [max_eat_times]\n"
# define WRONG_INPUT_MSG_LEN 92

# define MONITOR_FREQUENSY_US 500
# define USLEEP_LENGTH 100

struct	s_philo;

typedef struct s_config
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat_times;
	bool			stop;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_write;
	pthread_mutex_t	mutex_stop;
	struct s_philo	*first_philo;
}					t_config;

typedef struct s_philo
{
	int				id;
	int				eat_counter;
	pthread_mutex_t	mutex_eating;
	struct timeval	last_eat_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	mutex_counter;
	struct s_philo	*next;
	struct s_config	*config;
}					t_philo;

int					atoi_positive(char *str);
void				*philosopher_routine(void *arg);
void				*monitor_routine(void *params);
void				pick_up_forks(t_philo *philo);
void				put_down_forks(t_philo *philo);
long				current_time_in_ms(void);
long				time_diff_in_ms(struct timeval start, struct timeval end);
void				ft_putnbr_fd(unsigned long long n, int fd);

void				philo_sleep(int duration_ms, t_config *config);
void				philo_print(const char *message, t_philo *philo);
void				philo_take_forks_and_eat(t_philo *philo);

t_philo				*initiate_philos(t_config *config);
t_config			*init_config(int argc, char **argv);
int					create_threads(pthread_t **threads, t_philo *philos,
						t_config *config);

void				free_philos(t_philo *philos);
void				cleanup(t_philo *philos, pthread_t *threads,
						t_config *config);

bool				check_config_stop(t_config *config);
void				set_config_stop(t_config *config, bool status);
int					get_eat_counter(t_philo *philo);
void				increment_eat_counter(t_philo *philo);

int					handle_thread_creation_error(t_philo *philos,
						pthread_t *threads, t_config *config,
						int created_threads);
int					join_threads(pthread_t *threads, int created_threads);
int					start_monitor_thread(t_config *config,
						pthread_t *monitor_thread);
int					create_threads(pthread_t **threads, t_philo *philos,
						t_config *config);
int	death_check(t_philo *philo, t_config *config);

#endif