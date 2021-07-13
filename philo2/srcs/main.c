#include "philosopher.h"

void	check_starvation(t_philo *philo)
{
	int		i;
	long	time;

	msleep(MIN_TIME_IN_MS);
	while (!philo->end_of_philo)
	{
		i = 0;
		time = get_microsec();
		while (i < philo->params.n && !philo->end_of_philo)
		{
			if (time - philo->thread_arg[i].time_last_eat >= philo->params.time_to_die * 1000)
			{
				philo_state(&(philo->thread_arg[i]), DEATH);
				return ;
			}
			i++;
		}
		usleep(500);
	}
}

int	check_end_of_philo(t_thread_arg *args)
{
	if (args->params->must_eat_to_end > 0)
	{
		if (args->eat_counter == args->params->must_eat_to_end)
		{
			pthread_mutex_lock(args->mutex);
			(*args->num_philo_done)++;
			pthread_mutex_unlock(args->mutex);
		}
		if ((*args->num_philo_done) == args->params->n)
		{
			pthread_mutex_lock(args->mutex);
			(*args->end_of_philo) = 1;
			pthread_mutex_unlock(args->mutex);
			return (1);
		}
	}
	return (0);
}

/*
**	Function to be called when a philosopher is created 
*/

void	*philo_life(void *thread_arg)
{
	t_thread_arg *args;

	args = (t_thread_arg *) thread_arg;

	args->start_time = get_microsec();
	args->time_last_eat = args->start_time;
	while (!(*args->end_of_philo))
	{
		philo_eat(args);
		// if (check_end_of_philo(args))
		// 	break ;
		philo_sleep(args);
		// if (check_end_of_philo(args))
		// 	break ;
		philo_think(args);
		if (check_end_of_philo(args))
			break ;
	}
	return (NULL);
}

int	free_program(t_philo *philo)
{
	if (philo->tid)
	{
		free(philo->tid);
		philo->tid = NULL;
	}
	if (philo->thread_arg)
	{
		free(philo->thread_arg);
		philo->thread_arg = NULL;
	}
	if (philo->forks)
	{
		free(philo->forks);
		philo->forks = NULL;
	}
	return (1);
}

int	launch_threads(t_philo *philo, int n)
{
	int i;
	
	philo->global_start = get_microsec();
	i = 0;
	while (i < n)
	{
		philo->thread_arg[i].global_start = &(philo->global_start);
		if (pthread_create(&(philo->tid[i]), NULL,
			&philo_life, (void *)&(philo->thread_arg[i])))
			return (1);
		i += 2;
		usleep(20);
	}
	usleep(100);
	i = 1;
	while (i < n)
	{
		philo->thread_arg[i].global_start = &(philo->global_start);
		if (pthread_create(&(philo->tid[i]), NULL,
			&philo_life, (void *)&(philo->thread_arg[i])))
			return (1);
		i += 2;
		usleep(20);
	}
	return (0);
}

/*
**  params: number_of_philosophers, time_to_die, time_to_eat, time_to_sleep
**          number_of_times_each_philosopher_must_eat (optional)
*/

int main(int argc, char **argv)
{
	t_philo 		philo;

	if (parse_arguments(&philo.params, argc, argv) != 0)
	{
		printf(RED "Error: Invalid argument\n" RESET);
		return (EXIT_FAILURE);
	}
	if (t_philo_init(&philo, philo.params.n) != 0)
	{
		perror(RED "Error: Malloc failed in t_philo_init\n" RESET);
		return (EXIT_FAILURE);
	}
	if (thread_arg_init(&philo, philo.params.n) != 0)
	{
		perror(RED "Error: Init thread_arg_init failed\n" RESET);
		return (EXIT_FAILURE);
	}
	if (launch_threads(&philo, philo.params.n) != 0)
	{
		perror(RED "Error: thread launched failed\n" RESET);
		return (EXIT_FAILURE);
	}

	check_starvation(&philo);

	int i = 0;
	while (i < philo.params.n)
	{
		if (pthread_join((philo.tid[i]), NULL))
			return (1);
		i++;
	}

	// i = 0;
	// while (i < philo.params.n)
	// {
	// 	pthread_mutex_destroy(&(philo.forks[i]));
	// 	i++;
	// }
	// pthread_mutex_destroy(&(philo.mutex));

	//detach thread when no longer needed.

	free_program(&philo);
	return (0);
}
