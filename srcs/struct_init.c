/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 11:26:12 by cduvivie          #+#    #+#             */
/*   Updated: 2021/07/14 11:26:13 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	philo_init_mutex(t_philo *philo, int n)
{	
	int	i;

	i = 0;
	if (pthread_mutex_init(&(philo->mutex), NULL) != 0)
		return (1);
	while (i < n)
	{
		if (pthread_mutex_init(&(philo->forks[i]), NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

/*
**  arguments to be passed to each thread at moment of creation.
*/

int	thread_arg_init(t_philo *philo, int n)
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
		thread_arg->forks = philo->forks;
		thread_arg->eat_counter = 0;
		thread_arg->num_philo_done = &philo->num_philo_done;
		thread_arg->time_last_eat = 0;
		thread_arg->mutex = &philo->mutex;
		thread_arg->end_of_philo = &philo->end_of_philo;
		philo_i++;
	}
	return (0);
}

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
		return (exit_error(philo, MALLOC_FAILED));
	philo->thread_arg = (t_thread_arg *)malloc(sizeof(t_thread_arg) * n);
	if (!philo->thread_arg)
		return (exit_error(philo, MALLOC_FAILED));
	philo->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n);
	if (!philo->forks)
		return (exit_error(philo, MALLOC_FAILED));
	if (philo_init_mutex(philo, n) != 0)
		return (exit_error(philo, MUTEX_FAILED));
	thread_arg_init(philo, n);
	return (0);
}
