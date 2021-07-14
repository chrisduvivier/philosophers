/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 11:26:06 by cduvivie          #+#    #+#             */
/*   Updated: 2021/07/14 11:27:28 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_state_helper(int state)
{
	if (state == GRAB_FORK)
		printf(" has taken a fork\n");
	else if (state == EAT)
		printf(" is eating\n");
	else if (state == SLEEP)
		printf(" is sleeping\n");
	else if (state == THINK)
		printf(" is thinking\n");
	else if (state == DEATH)
		printf(" died\n");
	printf(RESET RESET_STYLE);
}

/**
 * @brief: print state of philo with timestamp.
 * 		   Assumes the mutex_lock during function call
 *
 * @param args: philo env variables
 * @param now: current time in ns
 * @param state: state of philosopher
 */

void	print_state(t_thread_arg *args, long long now, int state)
{
	if (state == EAT)
		printf(BLU);
	else if (state == DEATH)
		printf(RED);
	else if (state == SLEEP)
		printf(DIM);
	printf("%-10lld %i", (now - (*args->global_start)) / 1000,
		args->philo_i + 1);
	print_state_helper(state);
}

void	philo_state(t_thread_arg *args, int state)
{
	long long	now;
	int			i;

	i = 0;
	now = get_microsec();
	pthread_mutex_lock(args->mutex);
	if (*args->end_of_philo)
	{
		pthread_mutex_unlock(args->mutex);
		return ;
	}
	print_state(args, now, state);
	if (state == DEATH)
	{	
		*args->end_of_philo = 1;
		while (i < args->params->n)
			pthread_mutex_unlock(&args->forks[i++]);
	}
	pthread_mutex_unlock(args->mutex);
}
