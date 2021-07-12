#include "philosopher.h"

int	pick_forks(t_thread_arg *args)
{
	pthread_mutex_lock(&args->f_locks[args->left_hand]);
	args->forks[args->left_hand] = NOT_AVAILABLE;
	philo_fork(args);
	if (check_starvation(args) == 1)
	{
		pthread_mutex_unlock(&args->f_locks[args->right_hand]);
		return (1);
	}	
	pthread_mutex_lock(&args->f_locks[args->right_hand]);
	args->forks[args->right_hand] = NOT_AVAILABLE;
	philo_fork(args);
	if (check_starvation(args) == 1)
	{
		pthread_mutex_unlock(&args->f_locks[args->right_hand]);
		return (1);
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

	args->start_time = gettime_in_ms();
	args->time_last_eat = args->start_time;
	while (check_stop_philo(args) == 0)
	{
		if (pick_forks(args) != 0)
			break ;
		if (check_stop_philo(args) != 0)
			break ;

		philo_eat(args);
		if (check_stop_philo(args) != 0)
			break ;
		philo_sleep(args);
		philo_think(args);
	}
	unlock_mutex(args);
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
	if (philo->eat_counter)
	{
		free(philo->eat_counter);
		philo->eat_counter = NULL;
	}
	if (philo->f_locks)
	{
		free(philo->f_locks);
		philo->f_locks = NULL;
	}
	return (1);
}

int	launch_threads(t_philo *philo, int n)
{
	int i;
	
	i = 0;
	while (i < n)
	{
		if (pthread_create(&(philo->tid[i]), NULL, &philo_life, (void *)&(philo->thread_arg[i])))
			return (1);
		i += 2;
		usleep(20);
	}
	usleep(100);
	i = 1;
	while (i < n)
	{
		if (pthread_create(&(philo->tid[i]), NULL, &philo_life, (void *)&(philo->thread_arg[i])))
			return (1);
		i += 2;
		usleep(20);
	}


	i = 0;
	while (i < n)
	{
		//make it wait for the end of thread before exit main.
		if (pthread_join((philo->tid[i]), NULL))
			return (1);
		i++;
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

	if (parse_arguments(&philo.args, argc, argv) != 0)
	{
		printf(RED "Error: Invalid argument\n" RESET);
		return (EXIT_FAILURE);
	}
	if (t_philo_init(&philo, philo.args.number_of_philosophers) != 0)
	{
		perror(RED "Error: Malloc failed in t_philo_init\n" RESET);
		return (EXIT_FAILURE);
	}
	if (thread_arg_init(&philo, philo.args.number_of_philosophers) != 0)
	{
		perror(RED "Error: Init thread_arg_init failed\n" RESET);
		return (EXIT_FAILURE);
	}
	if (launch_threads(&philo, philo.args.number_of_philosophers) != 0)
	{
		perror(RED "Error: thread was not launched\n" RESET);
		return (EXIT_FAILURE);
	}
	
	int i = 0;
	while (i < philo.args.number_of_philosophers)
	{
		pthread_mutex_destroy(&philo.f_locks[i]);
		i++;
	}
	pthread_mutex_destroy(&philo.output_lock);

	//detach thread when no longer needed.

	return (0);
}
