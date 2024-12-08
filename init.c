/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:30:47 by scarlucc          #+#    #+#             */
/*   Updated: 2024/12/08 19:42:54 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(char **argv, t_data *table, int count)
{
	table->forks = malloc(sizeof(t_mtx) * ft_atoi(argv[1]));
	if (!table->forks)
		return (error("	malloc forks failed"), 1);
	while (++count < table->p_total)
	{
		if (pthread_mutex_init(&table->forks[count], NULL) != 0)
			return (error("	init forks failed"), 1);
	}
	return (0);
}

int	init_philos(char **argv, t_data *table, int count)
{
	t_philo	*philo;

	count = -1;
	table->philos = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!table->philos)
		return (error("	malloc philos failed"), 1);
	while (++count < table->p_total)
	{
		philo = &table->philos[count];
		philo->p_id = count + 1;
		philo->meal_count = 0;
		philo->full = 0;
		philo->when_last_meal = table->prog_start;
		if (pthread_mutex_init(&philo->meal_mtx, NULL))
			return (error("	failed to init meal_mtx"), 1);
		philo->f_left = &table->forks[count];
		philo->f_right = &table->forks[(count + 1) % table->p_total];
		philo->data = table;
	}
	return (0);
}

int	init_sim(char **argv, t_data *table, int count)
{
	table->p_total = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->max_meals = ft_atoi(argv[5]);
	else
		table->max_meals = 0;
	table->prog_start = whats_the_time();
	if (table->prog_start == -1)
		return (error("	failed to get time program start"), 1);
	table->stop = 0;
	if (pthread_mutex_init(&table->stop_mtx, NULL))
		return (error("	failed to init stop_mtx"), 1);
	if (pthread_mutex_init(&table->msg, NULL))
		return (error("	failed to init msg"), 1);
	if (init_forks(argv, table, count))
		return (1);
	if (init_philos(argv, table, count))
		return (1);
	return (0);
}

int	stop_sim(t_data	*data)
{
	pthread_mutex_lock(&data->stop_mtx);
	if (data->stop)
		return (pthread_mutex_unlock(&data->stop_mtx), 1);
	return (pthread_mutex_unlock(&data->stop_mtx), 0);
}

int	check_all_full(t_data	*data, int count)
{
	if (data->philos[count].full == 0)
		return (0);
	else if ((count + 1) == data->p_total)
	{
		pthread_mutex_unlock(&data->philos[count].meal_mtx);
		pthread_mutex_lock(&data->stop_mtx);
		data->stop = 1;
		pthread_mutex_unlock(&data->stop_mtx);
		return (-1);
	}
	else
		return (1);
}
