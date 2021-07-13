
#include "philosopher.h"

/*
**	verify correctness of passed arguments. Return non 0 value upon error. 
*/

int	check_error_in_arguments(t_params *args)
{
	if (args->n < 0 || args->time_to_die < 0 || args->time_to_eat < 0
		|| args->time_to_sleep < 0 || args->must_eat_to_end < 0)
	{
		printf("Error: Arguments must be positive integer\n");
		return (1);
	}
	if (args->n == 1 || args->n > 200)
	{
		printf("Error: number of philosophers must be between 2 to 200\n");
		return (1);
	}
	if (args->time_to_die < MIN_TIME_IN_MS
		|| args->time_to_eat < MIN_TIME_IN_MS
		|| args->time_to_sleep < MIN_TIME_IN_MS)
	{
		printf("Error: each time argument must be more than 60ms\n");
		return (1);
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

int parse_arguments(t_params *args, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		perror("Error: Wrong number of arguments\n");
		return (1);
	}
	if (check_args_datatype(argc, argv) == 1)
	{
		perror("Error: Wrong data type in arguments\n");
		return (1);
	}
	args->n = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->must_eat_to_end = 0;
	if (argc == 6)
		args->must_eat_to_end = ft_atoi(argv[5]);
	return (check_error_in_arguments(args));
}
