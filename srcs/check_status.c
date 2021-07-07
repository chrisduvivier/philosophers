#include "philosopher.h"

int	check_starvation(t_thread_arg *args)
{
	long long now;
	
	now = gettime_in_ms();
	if (now - args->time_last_eat > args->time_to_die)
	{
		pthread_mutex_lock(args->output_lock);
		printf(RED "%lldms %i died\n" RESET, now - args->start_time, args->philo_i + 1);
		pthread_mutex_unlock(args->output_lock);
		(*args->stop_philo)++;
		return (1);
	}
	return (0);
}

/*
**	Check if all philos have eaten more than the define number of time
**	`must_eat_to_end` (given in optional argument of program).
**	If at least one of the philosopher didn't reach the number, return `0`.
**	`1` is return when the simulation should stop.
*/

int	check_eat_count(t_thread_arg *args)
{
	int i;

	i = 0;
	while (i < args->total_philo)
	{
		if (args->eat_counter[i] < args->must_eat_to_end)
			return (0);
		i++;
	}
	return (1);
}

/*
**	verify if simulation has to stop. returns 0 if no need to stop.
*/

int	check_stop_philo(t_thread_arg *args)
{
	if (*args->stop_philo > 0)
		return (1);
	if (args->must_eat_to_end > 0)
		return (check_eat_count(args));
	return (0);
}