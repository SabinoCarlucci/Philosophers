/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:30:47 by scarlucc          #+#    #+#             */
/*   Updated: 2024/12/05 17:33:44 by scarlucc         ###   ########.fr       */
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
	count = -1;
	table->philos = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!table->philos)
		return (error("	malloc philos failed"), 1);
	while (++count < table->p_total)
	{
		table->philos[count].p_id = count + 1;
		table->philos[count].meal_count = 0;
		if (argv[5])
			table->philos[count].full = 0;
		else
			table->philos[count].full = -1;//forse superfluo
		table->philos[count].when_last_meal = table->prog_start;
		if (pthread_mutex_init(&table->philos[count].meal_mtx, NULL))
			return (error("	failed to init meal_mtx"), 1);
		if ((count + 1) < table->p_total)
			table->philos[count].f_right = &table->forks[count + 1];
		else
			table->philos[count].f_right = &table->forks[0];
		table->philos[count].f_left = &table->forks[count];
		table->philos[count].data = table;
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
	//count = -1;//senza, init_philos potrebbe usare il valore di count alterato da init_forks
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

void	stop_and_unfork(t_data	*data)
{
	//int	f_count;

	//f_count = -1;
	pthread_mutex_lock(&data->stop_mtx);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mtx);
	/* while (++f_count < data->p_total)//evita che filosofi vivi restino con forchette in mano dopo una morte
		pthread_mutex_unlock(&data->forks[f_count]); */
}
