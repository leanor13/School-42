/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:55:03 by yioffe            #+#    #+#             */
/*   Updated: 2024/09/15 11:32:34 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/wait.h>

# define NEG_ERROR -1

# define WRONG_INPUT "Usage: ./philo_bonus number_of_philosophers time_to_die \
time_to_eat time_to_sleep [max_eat_times]\n"
# define WRONG_INPUT_MSG_LEN 92

# define MONITOR_FREQUENCY_US 10000

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
	//pid_t			*monitor_pids;
	struct s_philo			*philos;
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


int					atoi_positive(char *str);
void	philosopher_routine(t_philo *philo);
void	*monitor_routine(void *arg);
void				pick_up_forks(t_philo *philo);
void				put_down_forks(t_philo *philo);
long				current_time_in_ms(void);
long				time_diff_in_ms(struct timeval start, struct timeval end);
void				ft_putnbr_fd(unsigned long long n, int fd);

void				philo_sleep(int duration_ms, t_config *config);
void				philo_print(const char *message, t_philo *philo);
void				philo_take_forks_and_eat(t_philo *philo);

t_philo				*init_philos(t_config *config);
t_config			*init_config(int argc, char **argv);

void	cleanup(t_philo *philos, t_config *config);

bool				check_config_stop(t_config *config);
void				set_config_stop(t_config *config, bool status);
//int					get_eat_counter(t_philo *philo);
//void				increment_eat_counter(t_philo *philo);

void	handle_process_creation_error(t_philo *philos, pid_t *philos_pids, t_config *config, int created_processes);

//int	start_monitor_process(t_config *config, pid_t *monitor_pid);
int	create_processes(pid_t **pids, t_philo *philos, t_config *config);
int	wait_for_processes(t_config *config);
void int_to_string(int num, char *str);
void	kill_all_philos(t_config *config);
void	clear_existing_semaphores(void);
void	philo_print_debug(const char *message, t_philo *philo);
int start_monitor_thread(t_philo *philo);

#endif