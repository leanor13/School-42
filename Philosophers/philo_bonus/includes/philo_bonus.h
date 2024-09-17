/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:55:03 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/17 18:17:47 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define NEG_ERROR -1

# define WRONG_INPUT \
	"Usage: ./philo_bonus number_of_philosophers time_to_die \
time_to_eat time_to_sleep [max_eat_times]\n"
# define WRONG_INPUT_MSG_LEN 92

# define MONITOR_FREQUENCY_US 1000

struct	s_philo;

typedef struct s_config
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat_times;
	bool			stop;
	sem_t			*forks_sem;
	sem_t			*sem_write;
	sem_t			*sem_stop;
	sem_t			*sem_killer;
	sem_t			*sem_fed_up;
	struct s_philo	*philos;
}					t_config;

typedef struct s_philo
{
	int				id;
	pid_t			pid;
	int				eat_counter;
	struct timeval	last_eat_time;
	bool			is_dead;
	struct s_config	*config;
}					t_philo;

t_config			*init_config(int argc, char **argv);
int					init_philos(t_config *config);
int					init_processes(t_config *config);
int					validate_input(int argc, char **argv, int *arguments);

void				philosopher_routine(t_philo *philo);
int					start_monitor_thread(t_philo *philo);
void				*monitor_routine(void *arg);

void				philo_take_forks_and_eat(t_philo *philo);

bool				check_config_stop(t_config *config);
void				set_config_stop(t_config *config, bool status);

void				cleanup(t_config *config);
void				kill_all_philos(t_config *config);
int					wait_for_processes(t_config *config);

void				philo_sleep(int duration_ms, t_config *config);
void				philo_print(const char *message, t_philo *philo);
int					atoi_positive(char *str);
void				ft_putnbr_fd(unsigned long long n, int fd);
long				time_diff_in_ms(struct timeval start, struct timeval end);

//void				philo_print_debug(const char *message, t_philo *philo);

#endif