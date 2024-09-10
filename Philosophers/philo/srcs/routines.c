#include "../includes/philo.h"

void *monitor_routine(void *params) 
{
    t_config *config = (t_config *)params;
    t_philo *philo;
    struct timeval current_time;

    while (!config->stop) {

		gettimeofday(&current_time, NULL);
        // pthread_mutex_lock(&config->mutex_write);
        // printf("\n[MONITOR] Routine started at: %ld:%d (sec:usec)\n", current_time.tv_sec, current_time.tv_usec);
        // pthread_mutex_unlock(&config->mutex_write);

        philo = config->first_philo;
        while (philo) {
            pthread_mutex_lock(&philo->mutex_eating);
            gettimeofday(&current_time, NULL);

			long time_since_last_eat = time_diff_in_ms(philo->last_eat_time, current_time);

			// pthread_mutex_lock(&config->mutex_write);
			// printf("\n[MONITOR] Checking Philosopher %d:\n", philo->id);
            // printf("[MONITOR] Philosopher status: Alive = %s\n", philo->alive ? "true" : "false");
            // printf("[MONITOR] Time since last meal: %ld ms\n", time_since_last_eat);
            // printf("[MONITOR] Time to die: %d ms\n", config->time_to_die);
            // printf("[MONITOR] Current time: %ld ms\n", 
            //     (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
            // printf("[MONITOR] Last eat time: %ld ms\n", 
            //     (philo->last_eat_time.tv_sec * 1000) + (philo->last_eat_time.tv_usec / 1000));
            
			// pthread_mutex_unlock(&config->mutex_write);
			
            if (time_since_last_eat > config->time_to_die) {
                philo->alive = false;
                philo_print("died", philo);

				// pthread_mutex_lock(&config->mutex_write);
				// printf("\n[MONITOR] Philosopher %d died: time since last meal %ld ms (time to die %d ms)\n", 
                //     philo->id, time_since_last_eat, config->time_to_die);
				// pthread_mutex_unlock(&config->mutex_write);

                config->stop = true;
				pthread_mutex_unlock(&philo->mutex_eating);
				return (NULL);
            }
            pthread_mutex_unlock(&philo->mutex_eating);
            
            philo = philo->next;
        }
        usleep(500); 
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
		p_sleep(config->time_to_eat / 25, config);
	while (!config->stop && philo->alive)
	// add here check for maximum eat time
	{
		if (config->number_of_times_each_philosopher_must_eat != -1 && philo->eat_count >= config->number_of_times_each_philosopher_must_eat)
			// TODO: we need to check somewhere and stop if all philos eaten enough times.
    		break; // no need to continue if philo ate enough times
		if (config->stop || !philo->alive)
			break;
		philo_take_forks_and_eat(philo);
		if (config->stop || !philo->alive)
			break;
		philo_print("is sleeping", philo);

		gettimeofday(&start_sleep, NULL);

		p_sleep(config->time_to_sleep, config);

		gettimeofday(&end_sleep, NULL);

		long sleep_duration = time_diff_in_ms(start_sleep, end_sleep);
		// pthread_mutex_lock(&config->mutex_write);
		// printf("[SLEEP] Philosopher %d slept for %ld ms (requested: %d ms)\n", philo->id, sleep_duration, config->time_to_sleep);
		// pthread_mutex_unlock(&config->mutex_write);

		if (config->stop || !philo->alive)
			break;
		philo_print("is thinking", philo);
	}
	return (NULL);
}