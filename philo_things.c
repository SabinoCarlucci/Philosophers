/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_things.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:33:57 by scarlucc          #+#    #+#             */
/*   Updated: 2024/12/08 19:43:38 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_or_full(t_data	*data, int count, int all_full)
{
	while (1)
	{
		while (++count < data->p_total)
		{
			pthread_mutex_lock(&data->philos[count].meal_mtx);
			if ((whats_the_time() - data->philos[count].when_last_meal)
				>= data->time_to_die)
			{
				pthread_mutex_unlock(&data->philos[count].meal_mtx);
				pthread_mutex_lock(&data->stop_mtx);
				data->stop = 1;
				pthread_mutex_unlock(&data->stop_mtx);
				return (time_message(&data->philos[count], CYAN, DIED), 1);
			}
			if (all_full && data->max_meals)
			{
				all_full = check_all_full(data, count);
				if (all_full == -1)
					return (1);
			}
			pthread_mutex_unlock(&data->philos[count].meal_mtx);
		}
		count = -1;
		all_full = 1;
	}
}

void	philo_think(t_philo	*philo)
{
	time_message(philo, MAGENTA, THINK);
	pthread_mutex_lock(philo->f_right);
	time_message(philo, GREEN, FORK);
	pthread_mutex_lock(philo->f_left);
	time_message(philo, GREEN, FORK);
	philo_eat(philo);
}

void	philo_eat(t_philo	*philo)
{
	time_message(philo, YELLOW, EAT);
	pthread_mutex_lock(&philo->meal_mtx);
	philo->when_last_meal = whats_the_time();
	pthread_mutex_unlock(&philo->meal_mtx);
	if (usleep(philo->data->time_to_eat * 1000) != 0)
		error("	philo failed usleep while eating");
	pthread_mutex_unlock(philo->f_left);
	pthread_mutex_unlock(philo->f_right);
	philo->meal_count++;
	if (philo->meal_count == philo->data->max_meals)
		philo->full = 1;
	philo_sleep(philo);
}

void	philo_sleep(t_philo	*philo)
{
	if (stop_sim(philo->data))
		return ;
	time_message(philo, BLUE, SLEEP);
	if (usleep(philo->data->time_to_sleep * 1000) != 0)
		error("	philo failed usleep while sleeping");
}

void	*start_dinner(void *point)
{
	t_philo	*philo;

	philo = (t_philo *)point;
	if (philo->data->p_total == 1)
	{
		time_message(philo, MAGENTA, THINK);
		time_message(philo, GREEN, FORK);
		usleep(philo->data->time_to_die * 1000);
		return (point);
	}
	if (philo->p_id % 2 != 0)
		usleep(9000);
	while (1)
	{
		if (stop_sim(philo->data))
			break ;
		philo_think(philo);
	}
	return (point);
}
