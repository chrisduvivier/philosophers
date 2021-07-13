/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 16:33:30 by cduvivie          #+#    #+#             */
/*   Updated: 2021/07/14 00:53:45 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <sys/time.h>

# define GRAB_FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DEATH 5

# define MIN_TIME_IN_MS 60

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define WHT   "\x1B[37m"
# define DIM   "\e[2m"
# define RESET_STYLE   "\e[0m"
# define RESET "\x1B[0m"

typedef struct s_params
{
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat_to_end;
	int			n;
}				t_params;

/**
 * Struct to pass into thread create function.
 * Includes the number of philosopher i. 
 */
typedef struct s_thread_arg
{
	t_params		*params;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*mutex;
	int				philo_i;
	int				left_hand;
	int				right_hand;
	int				eat_counter;
	int				*num_philo_done;
	long long		start_time;
	long long		*global_start;
	long long		time_last_eat;
	int				*end_of_philo;
}					t_thread_arg;

/*
**	Struct that holds the list of threads, mutex lock, and arguments
**	related to the behavior of philosophers.
*/

typedef struct s_philo
{
	pthread_t		*tid;
	t_thread_arg	*thread_arg;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex;
	t_params		params;
	int				num_philo_done;
	int				end_of_philo;
	long long		global_start;
}					t_philo;

/*
**	Input parser
*/

int parse_arguments(t_params *args, int argc, char **argv);

/*
**	Struct init
*/

int	t_philo_init(t_philo *philo, int n);
int thread_arg_init(t_philo *philo, int philo_i);

/*
**	Philosopher's activity (status)
*/

void	philo_fork(t_thread_arg *args);
void	philo_eat(t_thread_arg *args);
void	philo_sleep(t_thread_arg *args);
void	philo_think(t_thread_arg *args);

/*
**	Check program/philosopher status
*/

void	check_starvation(t_philo *philo);
void    philo_state(t_thread_arg *args, int state);
int	check_eat_count(t_thread_arg *args);
int	check_stop_philo(t_thread_arg *args);

/*
**	Utility functions
*/

int	ft_atoi(const char *str);
int	ft_isdigit_string(const char *str);
int	ft_isdigit(int c);
int	free_program(t_philo *philo);
void	unlock_mutex(t_thread_arg *args);

/*
**	Time
*/

int	msleep(unsigned int tms);
long long	get_microsec(void);
long long	get_millisec(void);

/*
**	Some debug function for logs/testing purpose
*/

void    print_state_fork(int *forks, int size);
void	could_not_picked_up_fork(t_thread_arg *args);
void	release_fork(t_thread_arg *args);

#endif