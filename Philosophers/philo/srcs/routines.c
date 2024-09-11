#include "../includes/philo.h"

bool	check_config_stop(t_config *config)
{
	bool	status;

	pthread_mutex_lock(&config->mutex_stop);
	status = config->stop;
	pthread_mutex_unlock(&config->mutex_stop);
	return (status);
}

void	set_config_stop(t_config *config, bool status)
{
	pthread_mutex_lock(&config->mutex_stop);
	config->stop = status;
	pthread_mutex_unlock(&config->mutex_stop);
}

int	get_eat_counter(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->mutex_counter);
	result = philo->eat_counter;
	pthread_mutex_unlock(&philo->mutex_counter);
	return (result);
}

void	increment_eat_counter(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_counter);
	philo->eat_counter += 1;
	pthread_mutex_unlock(&philo->mutex_counter);
}

void *monitor_routine(void *params) 
{
    t_config *config = (t_config *)params;
    t_philo *philo;
    struct timeval current_time;
	int	done_philo;
	int	eat_counter;

    while (!config->stop) {

		gettimeofday(&current_time, NULL);

        philo = config->first_philo;
		done_philo = 0;
        while (philo) {
            pthread_mutex_lock(&philo->mutex_eating);
            //gettimeofday(&current_time, NULL);

			long time_since_last_eat = time_diff_in_ms(philo->last_eat_time, current_time);
			
            if (time_since_last_eat > config->time_to_die) {
				set_config_stop(config, true);
                philo_print("died", philo);
				pthread_mutex_unlock(&philo->mutex_eating);
				return (NULL);
            }
            pthread_mutex_unlock(&philo->mutex_eating);
			eat_counter = get_eat_counter(philo);
			if (config->max_eat_times >= 0 && eat_counter >= config->max_eat_times)
				done_philo ++;
            philo = philo->next;
        }
		if (config->max_eat_times >= 0 && done_philo == config->number_of_philosophers)
		{
			set_config_stop(config, true);
			return (NULL);
		}
        usleep(100); 
    }
    return (NULL);
}

void *philosopher_routine(void *params) {
	t_philo		*philo;
	t_config	*config;
	struct timeval start_sleep, end_sleep;

	philo = (t_philo *)params;
	config = philo->config;
	if (!config)
		return (NULL);
	if (philo->id % 2 && config->number_of_philosophers > 1)
		philo_sleep(config->time_to_eat / 50, config);
	
	while (!check_config_stop(config))
	// add here check for maximum eat time
	{
		//if (config->max_eat_times != -1 && philo->eat_counter >= config->max_eat_times)
			// TODO: we need to check somewhere and stop if all philos eaten enough times.
    	//	break; // no need to continue if philo ate enough times
		if (check_config_stop(config))
			break;

		philo_take_forks_and_eat(philo);

		if (check_config_stop(config))
			break;

		philo_print("is sleeping", philo);

		gettimeofday(&start_sleep, NULL);

		philo_sleep(config->time_to_sleep, config);

		gettimeofday(&end_sleep, NULL);

		if (check_config_stop(config))
			break;

		philo_print("is thinking", philo);
	}
	return (NULL);
}