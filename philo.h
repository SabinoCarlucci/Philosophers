//metti header dopo aver iniziato progetto

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> //printf
# include <stdlib.h> //malloc, free
# include <unistd.h> //usleep
# include <pthread.h> //thread and mutex
# include <sys/time.h> // gettimeofday

typedef pthread_mutex_t t_mtx;

typedef struct s_data t_data;

# define INT "2147483647\0"
# define PLUS_INT "+2147483647\0"
# define LONG "9223372036854775807\0"
# define PLUS_LONG "+9223372036854775807\0"


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

void	error(char *msg);


#endif