/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 16:33:30 by cduvivie          #+#    #+#             */
/*   Updated: 2021/07/12 14:22:23 by cduvivie         ###   ########.fr       */
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

# define AVAILABLE 0
# define NOT_AVAILABLE 1

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

typedef struct s_args
{
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat_to_end;
}				t_args;

/**
 * Struct to pass into thread create function.
 * Includes the number of philosopher i. 
 */
typedef struct s_thread_arg
{
	pthread_mutex_t	*f_locks;
	pthread_mutex_t	*output_lock;
	pthread_mutex_t	*stop_m;
	int				*forks;
	int				philo_i;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_to_end;
	int				total_philo;
	int				left_hand;
	int				right_hand;
	int				thinking;
	int				*eat_counter;
	long long		start_time;
	long long		time_last_eat;
	int				*stop_philo;
}					t_thread_arg;

/*
**	Struct that holds the list of threads, mutex lock, and arguments
**	related to the behavior of philosophers.
*/

typedef struct s_philo
{
	pthread_t		*tid;
	int				*forks;
	t_thread_arg	*thread_arg;
	pthread_mutex_t	*f_locks;
	t_args			args;
	pthread_mutex_t	output_lock;
	int				*eat_counter;
	pthread_mutex_t	stop_m;
	int				stop_philo;
}					t_philo;

/*
**	Input parser
*/

int parse_arguments(t_args *args, int argc, char **argv);

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

int	check_starvation(t_thread_arg *args);
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
long long gettime_in_ms(void);

/*
**	Some debug function for logs/testing purpose
*/

void    print_state_fork(int *forks, int size);
void	could_not_picked_up_fork(t_thread_arg *args);
void	release_fork(t_thread_arg *args);

#endif