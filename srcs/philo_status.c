#include "philosopher.h"

void	picked_up_fork(t_thread_arg *args)
{
	pthread_mutex_lock(args->output_lock);
	printf("%-10lldms %i has taken a fork\n", gettime_in_ms() - args->start_time, args->philo_i + 1);
	pthread_mutex_unlock(args->output_lock);
}

/*
**	The timestamp of `time_last_eat` is reset at
**	the beginning of the eating process.
*/

void	philo_eat(t_thread_arg *args)
{
	long long	eat_time;

	eat_time = gettime_in_ms();
	pthread_mutex_lock(args->output_lock);
	printf(BLU "%-10lldms %i is eating\n" RESET, eat_time - args->start_time, args->philo_i + 1);
	pthread_mutex_unlock(args->output_lock);
	args->time_last_eat = eat_time;
	msleep(args->time_to_eat);
}

void	philo_sleep(t_thread_arg *args)
{
	pthread_mutex_lock(args->output_lock);
	printf(DIM "%-10lldms %i is sleeping\n" RESET_STYLE, 
		gettime_in_ms() - args->start_time, args->philo_i + 1);
	pthread_mutex_unlock(args->output_lock);
	msleep(args->time_to_sleep);
}

void	philo_think(t_thread_arg *args)
{
	pthread_mutex_lock(args->output_lock);
	printf("%-10lldms %i is thinking\n", gettime_in_ms() - args->start_time, args->philo_i + 1);
	pthread_mutex_unlock(args->output_lock);
}
