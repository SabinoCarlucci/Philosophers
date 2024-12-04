/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:21:25 by scarlucc          #+#    #+#             */
/*   Updated: 2024/12/04 14:51:35 by scarlucc         ###   ########.fr       */
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

//define philo messages
# define FORK "has taken a fork\n"
# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define DIED "died\n"

//define colors
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define RED "\033[0;31m"
# define NO_COLOR "\033[0m"

//define compare for parsing
# define LIM_PHILO "200\0"
# define INT "2147483647\0"
# define LIM_TIME 59 //since operator is <=, I use 59

//define errors
# define ERR_IN_NUM "	input must be 5 or 6 values"
# define ERR_USAGE "	Usage:  ./philo 5 800 200 200 [5]"
# define ERR_LIMIT "	input beyond limit"
# define ERR_LIMIT_LOW "	input below limit"
# define ERR_NUM "	input must be a number"
# define ERR_GETTIME "	clock is broken"

typedef struct s_philo
{
	int			p_id;
	int			meal_count;
	int			full;//e' necessaria? non posso usare meal count?
	int			when_last_meal;
	t_mtx		*f_right;
	t_mtx		*f_left;
	pthread_t	thread;//identificatore thread creato con pthread_create
	t_data		*data;
}				t_philo;

struct s_data
{
	int		p_total;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		max_meals; // [5] optional
	int		prog_start; // timestamp start program
	int		stop;
	t_mtx	stop_mtx;
	t_mtx	msg;
	t_mtx	*forks; // array forks
	t_philo	*philos; //array philosophers
};

//utils.c
void	time_message(t_philo	*philo, const char	*color, const char	*message);
void	cleanup(t_data *table);
int		whats_the_time(void);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *nptr);


//parsing.c
void	error(const char *msg);
int		is_num(char *arg);
int		check_limits(char *arg, char *high_compare, int low_compare);
int		parsing(int argc, char **argv, int n_input);

//init.c
int		init_forks(char **argv, t_data *table, int count);
int		init_philos(char **argv, t_data *table, int count);
int		init_sim(char **argv, t_data *table, int count);
int		stop_sim(t_data	*data);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

//philo_things.c
int		dead_or_full(t_data	*data, int	count, int f_count);
void	philo_think(t_philo	*philo);
void	philo_eat(t_philo	*philo);
void	philo_sleep(t_philo	*philo);
void	*start_dinner(void *point);

#endif