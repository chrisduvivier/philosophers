#include "philosopher.h"

/*
**	
*/

int	try_pick_fork_left(t_thread_arg *args)
{
	int left;
	
	left = (args->philo_i);
	if (args->left_hand == 0)
	{
		if (args->forks[left] != AVAILABLE)
		{
			pthread_mutex_unlock(&args->lock);
			// could_not_picked_up_fork(args);
			// print_state_fork(args->forks, args->total_philo);
			if (args->thinking == 0)
			{
				philo_think(args);
				args->thinking = 1;
			}
			//check starvation
			check_starvation(args);
			return (1);
		}
		args->forks[left] = NOT_AVAILABLE;
		args->left_hand = 1;
		picked_up_fork(args);
	}
	return (0);
}

/*
**	
*/

int	try_pick_fork_right(t_thread_arg *args)
{
	int right;
	
	right = (args->philo_i + 1) % args->total_philo;
	if (args->right_hand == 0)
	{
		if (args->forks[right] != AVAILABLE)
		{
			pthread_mutex_unlock(&args->lock);
			// could_not_picked_up_fork(args);
			// print_state_fork(args->forks, args->total_philo);
			if (args->thinking == 0)
			{
				philo_think(args);
				args->thinking = 1;
			}
			//check starvation
			check_starvation(args);
			return (1); //continue ;
		}
		args->forks[right] = NOT_AVAILABLE;
		args->right_hand = 1;
		picked_up_fork(args);
	}
	return (0);
}

/*
**	Function to be called when a philosopher is created 
*/

void	*philo_life(void *thread_arg)
{
	t_thread_arg *args;

	//args init
	args = (t_thread_arg *) thread_arg;
	// printf("I am philosopher %d\n", args->philo_i + 1);
	// print_state_fork(args->forks, args->total_philo);

	args->time_last_eat = args->start_time;

	// activity
	while (check_stop_philo(args) == 0)
	{
		args->left_hand = 0;
		args->right_hand = 0;
		while (check_stop_philo(args) == 0 && (!args->left_hand || !args->right_hand))
		{
			// avoid deadlock by putting ordering
			if (args->philo_i + 1 == args->total_philo)
			{
				pthread_mutex_lock(&args->lock);
				if (try_pick_fork_right(args))
					continue ;
				if (try_pick_fork_left(args))
					continue ;
				pthread_mutex_unlock(&args->lock);
				}
			else 
			{
				pthread_mutex_lock(&args->lock);
				if (try_pick_fork_left(args))
					continue ;
				if (try_pick_fork_right(args))
					continue ;
				pthread_mutex_unlock(&args->lock);
			}
		}
		if (check_stop_philo(args) != 0)
			break ;
		args->thinking = 0;
		philo_eat(args);
		pthread_mutex_lock(&args->lock);
		args->forks[(args->philo_i)] = AVAILABLE;
		args->forks[((args->philo_i + 1) % args->total_philo)] = AVAILABLE;
		pthread_mutex_unlock(&args->lock);
		philo_sleep(args);
		(args->eat_counter[args->philo_i])++;
	}
	// exit
	// printf("Philosopher %d is done\n", args->philo_i + 1);
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
	return (1);
}

int	launch_threads(t_philo *philo, int n)
{
	int i;
	long long start_time;
	
	start_time = gettime_in_ms();
	i = 0;
	while (i < n)
	{
		philo->thread_arg[i].start_time = start_time;
		pthread_create(&(philo->tid[i]), NULL, &philo_life, (void *)&(philo->thread_arg[i]));
		i++;
	}
	i = 0;
	while (i < n)
	{
		pthread_join((philo->tid[i]), NULL);		//make it wait for the end of thread before exit main.
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
	launch_threads(&philo, philo.args.number_of_philosophers);
	
	int i = 0;
	while (i < philo.args.number_of_philosophers)
	{
		pthread_mutex_destroy(&philo.thread_arg->lock);
		i++;
	}

	//detach thread when no longer needed.

	return (0);
}
