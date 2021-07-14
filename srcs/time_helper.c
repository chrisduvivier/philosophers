/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 11:30:41 by cduvivie          #+#    #+#             */
/*   Updated: 2021/07/14 11:30:42 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long	get_millisec(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec) * 1000LL + (now.tv_usec) / 1000);
}

long long	get_microsec(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000000 + now.tv_usec);
}

/*
**	wrapper for the function usleep() which takes the duration in
**	micro seconds as input. This allows to pass in time in ms.
*/

int	msleep(unsigned int tms)
{
	return (usleep(tms * 999));
}
