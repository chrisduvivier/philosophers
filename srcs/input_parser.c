/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 11:25:55 by cduvivie          #+#    #+#             */
/*   Updated: 2021/07/14 11:26:38 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
**	verify correctness of passed arguments. Return non 0 value upon error. 
*/

int	check_error_in_arguments(t_params *args)
{
	if (args->n < 0 || args->time_to_die < 0 || args->time_to_eat < 0
		|| args->time_to_sleep < 0 || args->must_eat_to_end < 0)
	{
		exit_error(NULL, "Error: Arguments must be positive int\n");
		return (EXIT_FAILURE);
	}
	if (args->n == 1 || args->n > 200)
	{
		exit_error(NULL, "Error: num of philosophers must be between 2-200\n");
		return (EXIT_FAILURE);
	}
	if (args->time_to_die < MIN_TIME_IN_MS
		|| args->time_to_eat < MIN_TIME_IN_MS
		|| args->time_to_sleep < MIN_TIME_IN_MS)
	{
		exit_error(NULL, "Error: each time argument must be more than 60ms\n");
		return (EXIT_FAILURE);
	}
	return (0);
}

/*
**	verify correctness of passed arguments. Return non 0 value upon error. 
*/

int	check_args_datatype(int argc, char **argv)
{
	if (ft_isdigit_string(argv[1]) || ft_isdigit_string(argv[2])
		|| ft_isdigit_string(argv[3]) || ft_isdigit_string(argv[4]))
		return (1);
	if (argc == 6 && ft_isdigit_string(argv[5]))
		return (1);
	return (0);
}

/*
**	Fill arguments into structure and check for error input.
*/

int	parse_arguments(t_params *args, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (exit_error(NULL, "Error: Wrong number of arguments\n"));
	if (check_args_datatype(argc, argv) == 1)
		return (exit_error(NULL, "Error: Wrong data type in arguments\n"));
	args->n = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->must_eat_to_end = 0;
	if (argc == 6)
		args->must_eat_to_end = ft_atoi(argv[5]);
	return (check_error_in_arguments(args));
}
