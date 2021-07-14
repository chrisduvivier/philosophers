
#include "philosopher.h"

/*
**	verify correctness of passed arguments. Return non 0 value upon error. 
*/

int	check_error_in_arguments(t_args *args)
{
	if (args->number_of_philosophers < 0 || args->time_to_die < 0
			|| args->time_to_eat < 0 || args->time_to_sleep < 0
			|| args->must_eat_to_end < 0)
	{
		perror("Error: Arguments must be positive integer\n");
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

int parse_arguments(t_args *args, int argc, char **argv)
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
	args->number_of_philosophers = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->must_eat_to_end = 0;
	if (argc == 6)
		args->must_eat_to_end = ft_atoi(argv[5]);
	return (check_error_in_arguments(args));
}
