#include "philosopher.h"

int	t_philo_init(t_philo *philo, int n)
{
	philo->tid = NULL;
	philo->forks = NULL;
	philo->thread_arg = NULL;
	philo->eat_counter = NULL;
	philo->stop_philo = 0;

	philo->tid = (pthread_t *)malloc(sizeof(pthread_t) * n);
	if (!philo->tid)
		return (free_program(philo));
	philo->thread_arg = (t_thread_arg *)malloc(sizeof(t_thread_arg) * n);
	if (!philo->thread_arg)
		return (free_program(philo));
	philo->forks = (int *)malloc(sizeof(int) * n);
	if (philo->forks == NULL)
		return (free_program(philo));
	memset((void *)philo->forks, 0, sizeof(int) * n);
	philo->eat_counter = (int *)malloc(sizeof(int) * n);
	if (philo->eat_counter == NULL)
		return (free_program(philo));
	memset((void *)philo->eat_counter, 0, sizeof(int) * n);
	if (pthread_mutex_init(&(philo->output_lock), NULL) != 0)
	{
		printf(RED "Error: mutex init failed\n" RESET);
		return (free_program(philo));
	}
	return (0);
}

/*
**  arguments to be passed to each thread at moment of creation.
*/

int thread_arg_init(t_philo *philo, int n)
{
	int				philo_i;
	t_thread_arg	*thread_arg;

	philo_i = 0;
	while (philo_i < n)
	{
		thread_arg = &(philo->thread_arg[philo_i]);
		thread_arg->philo_i = philo_i;
		thread_arg->forks = philo->forks;
		thread_arg->time_to_die = philo->args.time_to_die;
		thread_arg->time_to_eat = philo->args.time_to_eat;
		thread_arg->time_to_sleep = philo->args.time_to_sleep;
		thread_arg->must_eat_to_end = philo->args.must_eat_to_end;
		thread_arg->eat_counter = philo->eat_counter;
		thread_arg->total_philo = n;
		thread_arg->left_hand = 0;
		thread_arg->right_hand = 0;
		thread_arg->thinking = 0;
		thread_arg->time_last_eat = 0;
		thread_arg->stop_philo = &philo->stop_philo;
		thread_arg->output_lock = &philo->output_lock;
		if (pthread_mutex_init(&(thread_arg->lock), NULL) != 0)
		{
			printf(RED "Error: mutex init failed\n" RESET);
			return (free_program(philo));
		}
		philo_i++;
	}
	return (0);
}
