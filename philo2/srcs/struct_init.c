#include "philosopher.h"

/*
**	Initialize variables, allocate memory, and set their value.
*/

int	t_philo_init(t_philo *philo, int n)
{
	philo->tid = NULL;
	philo->forks = NULL;
	philo->thread_arg = NULL;
	philo->end_of_philo = 0;
	philo->num_philo_done = 0;

	philo->tid = (pthread_t *)malloc(sizeof(pthread_t) * n);
	if (!philo->tid)
		return (free_program(philo));

	philo->thread_arg = (t_thread_arg *)malloc(sizeof(t_thread_arg) * n);
	if (!philo->thread_arg)
		return (free_program(philo));
	
	philo->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n);
	if (!philo->forks)
		return (free_program(philo));
	
	if (pthread_mutex_init(&(philo->mutex), NULL) != 0)
	{
		printf(RED "Error: mutex init failed\n" RESET);
		return (free_program(philo));
	}

	int i;
	i = 0;
	while (i < n)	
	{
		if (pthread_mutex_init(&(philo->forks[i]), NULL) != 0)
		{
			printf(RED "Error: mutex init failed\n" RESET);
			return (free_program(philo));
		}
		i++;
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
		thread_arg->params = &(philo->params);
		thread_arg->philo_i = philo_i;
		thread_arg->left_hand = philo_i;
		thread_arg->right_hand = (philo_i + 1) % n;
		thread_arg->forks = philo->forks;		//maybe add ptr
		thread_arg->eat_counter = 0;
		thread_arg->num_philo_done = &philo->num_philo_done;
		thread_arg->time_last_eat = 0;
		thread_arg->mutex = &philo->mutex;
		thread_arg->end_of_philo = &philo->end_of_philo;
		philo_i++;
	}
	return (0);
}
