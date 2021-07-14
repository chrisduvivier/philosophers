/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 11:27:40 by cduvivie          #+#    #+#             */
/*   Updated: 2021/07/14 11:28:00 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	pick_forks(t_thread_arg *args)
{
	pthread_mutex_lock(&(args->forks[args->left_hand]));
	philo_state(args, GRAB_FORK);
	pthread_mutex_lock(&(args->forks[args->right_hand]));
	philo_state(args, GRAB_FORK);
}

void	philo_eat(t_thread_arg *args)
{
	pick_forks(args);
	args->time_last_eat = get_microsec();
	philo_state(args, EAT);
	msleep(args->params->time_to_eat);
	pthread_mutex_unlock(&(args->forks[args->left_hand]));
	pthread_mutex_unlock(&(args->forks[args->right_hand]));
	args->eat_counter += 1;
}

void	philo_sleep(t_thread_arg *args)
{
	philo_state(args, SLEEP);
	msleep(args->params->time_to_sleep);
}

void	philo_think(t_thread_arg *args)
{
	philo_state(args, THINK);
}
