#include "philosopher.h"

void    print_state_fork(int *forks, int size)
{
	int i;

	i = 0;
	printf("forks: ");
	while (i < size)
	{
		printf("[%d] ", forks[i]);
		i++;
	}
	printf("\n");
}

void	could_not_picked_up_fork(t_thread_arg *args)
{
	pthread_mutex_lock(args->output_lock);
	printf("%lld %i could not take a fork\n", args->start_time - gettime_in_ms(), args->philo_i + 1);
	pthread_mutex_unlock(args->output_lock);
}

void	release_fork(t_thread_arg *args)
{
	pthread_mutex_lock(args->output_lock);
	printf("%lld %i released fork\n", args->start_time - gettime_in_ms(), args->philo_i + 1);
	pthread_mutex_unlock(args->output_lock);
}