/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_things.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:33:57 by scarlucc          #+#    #+#             */
/*   Updated: 2024/12/05 18:03:25 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_or_full(t_data	*data, int	count, int	all_full)
{
	while (1)
	{
		while (++count < data->p_total)
		{
			pthread_mutex_lock(&data->philos[count].meal_mtx);//mutex per tempo ultimo pasto
			if ((whats_the_time() - data->philos[count].when_last_meal)
					>= data->time_to_die)
			{
				pthread_mutex_unlock(&data->philos[count].meal_mtx);//mutex per tempo ultimo pasto
				stop_and_unfork(data);
				return (time_message(&data->philos[count], CYAN, DIED), 1);//potrebbe ritardare il messaggio di morte, nel caso sposta sopra ciclo sblocca-forchette			
			}
			//pthread_mutex_unlock(&data->philos[count].meal_mtx);//mutex per tempo ultimo pasto
			//pthread_mutex_lock(&data->philos[count].meal_mtx);//mutex per tempo ultimo pasto
			if (all_full && data->max_meals)//controllo se pieni tutti
			{
				if (data->philos[count].full == 0)
					all_full = 0;
				else if ((count + 1) == data->p_total)
				{
					pthread_mutex_unlock(&data->philos[count].meal_mtx);//mutex per tempo ultimo pasto
					stop_and_unfork(data);
					return (1);
				}
			}
			pthread_mutex_unlock(&data->philos[count].meal_mtx);//mutex per tempo ultimo pasto	
		}
		count = -1;
		all_full = 1;
	}
}

void	philo_think(t_philo	*philo)
{
	t_data	*data;

	data = philo->data;
	if (time_message(philo, MAGENTA, THINK))
		return ;	
	pthread_mutex_lock(philo->f_right);
	if (time_message(philo, GREEN, FORK))
	{
		pthread_mutex_unlock(philo->f_right);
		return ;
	}
	if (philo->data->p_total == 1)
	{
		usleep(philo->data->time_to_die * 1000);
		pthread_mutex_unlock(philo->f_right);
		return ;
	}
	philo_eat(philo);
}

void	philo_eat(t_philo	*philo)
{
	pthread_mutex_lock(philo->f_left);
	if (time_message(philo, GREEN, FORK))
	{
		pthread_mutex_unlock(philo->f_right);
		pthread_mutex_unlock(philo->f_left);
		return ;
	}
	if (time_message(philo, YELLOW, EAT))
	{
		pthread_mutex_unlock(philo->f_right);
		pthread_mutex_unlock(philo->f_left);
		return ;
	}
	pthread_mutex_lock(&philo->meal_mtx);//mutex per tempo ultimo pasto
	philo->when_last_meal = whats_the_time();//e' giusto accedere a questa risorsa con meal_mtx? negli altri casi uso msg
	pthread_mutex_unlock(&philo->meal_mtx);//mutex per tempo ultimo pasto
	if (usleep(philo->data->time_to_eat * 1000) != 0)
		error("	philo failed usleep while eating");
	pthread_mutex_unlock(philo->f_right);
	pthread_mutex_unlock(philo->f_left);
	philo->meal_count++;
	if (philo->meal_count == philo->data->max_meals)//forse mutex
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
	philo_think(philo);
}

void	*start_dinner(void *point)
{
	t_philo	*philo;

	philo = (t_philo *)point;
	if (philo->p_id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (stop_sim(philo->data))
			break ;
		philo_think(philo);
	}
	return (point);
}
