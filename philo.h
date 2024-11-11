/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:21:25 by scarlucc          #+#    #+#             */
/*   Updated: 2024/11/11 16:59:45 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> //printf
# include <stdlib.h> //malloc, free
# include <unistd.h> //usleep
# include <pthread.h> //thread and mutex
# include <sys/time.h> // gettimeofday

typedef pthread_mutex_t	t_mtx;

typedef struct s_data	t_data;

//define compare for parsing
# define INT "2147483647\0"
# define LONG "9223372036854775807\0"

//define errors
# define ERR_USAGE "Usage:  ./philo 5 800 200 200 [5]"
# define ERR_LIMIT "Input beyond limit"
# define ERR_NUM "input non numerico"

//define colors
# define NO_COLOR "\033[0m"
# define YELLOW "\033[0;33m"
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define CYAN "\033[0;36m"
# define MAGENTA "\033[0;35m"

typedef struct s_fork
{
	t_mtx	fork;
	int		f_id;
}			t_fork;

typedef struct s_philo
{
	int			p_id;
	int			meal_count;
	int			full;
	long		when_last_meal;
	t_fork		f_right;
	t_fork		f_left;
	pthread_t	thread_id;
	t_data		*data;
}				t_philo;

/* 
	global data

	./philo 5 800 200 200 [5]
 */
struct s_data
{
	int		p_total;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	max_meals; // [5] optional
	long	prog_start; // timestamp start program
	int		prog_end; // timestamp end program
	t_fork	*forks; // array forks
	t_philo	*philos; //array philosophers
};

//utils.c
void	error(char *msg);
size_t	ft_strlen(const char *s);

//parsing.c
int		is_num(char *arg);
int		check_limits(char *arg, char *compare);
int		parsing(char **argv);

#endif