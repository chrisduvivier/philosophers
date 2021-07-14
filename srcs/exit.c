/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 10:34:17 by cduvivie          #+#    #+#             */
/*   Updated: 2021/07/14 11:23:38 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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

int	exit_error(t_philo *philo, char *msg)
{
	if (msg)
		printf(RED "%s" RESET, msg);
	if (philo)
		free_program(philo);
	return (EXIT_FAILURE);
}
