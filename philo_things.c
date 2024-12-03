/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_things.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:33:57 by scarlucc          #+#    #+#             */
/*   Updated: 2024/12/03 18:13:18 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_or_full(t_data	*data, int	count)
{
	while (1)
	{
		while (++count < data->p_total)
		{
			if ((whats_the_time() - data->philos[count].when_last_meal)
					>= data->time_to_die)
			{
				pthread_mutex_lock(&data->stop_mtx);
				data->stop = 1;
				pthread_mutex_unlock(&data->stop_mtx);
				int	i = -1;//fai in modo corretto
				while (++i < data->p_total)//evita che filosofi vivi restino con forchette in mano dopo una morte
				{
					pthread_mutex_unlock(data->philos[i].f_right);
					pthread_mutex_unlock(data->philos[i].f_left);
				}
				return (time_message(&data->philos[count], CYAN, DIED), 1);//potrebbe ritardare il messaggio di morte, nel caso sposta sopra ciclo sblocca-forchette			
			}
			//controllo se pieni tutti
			//else
				
				
		}
		count = -1;
	}
}

void	philo_think(t_philo	*philo)
{
	t_data	*data;

	data = philo->data;
	if (stop_sim(data))
		return ;
	time_message(philo, MAGENTA, THINK);	
	if (stop_sim(data))
		return ;
	pthread_mutex_lock(philo->f_right);
	if (stop_sim(data))
	{
		pthread_mutex_unlock(philo->f_right);
		return ;
	}
	time_message(philo, GREEN, FORK);
	//metti custom per caso 1 solo filosofo: ma serve?

	/* pthread_mutex_lock(philo->f_left);
	if (stop_sim(data))
	{
		pthread_mutex_unlock(philo->f_right);
		pthread_mutex_unlock(philo->f_left);
		return ;
	}
	time_message(philo, GREEN, FORK);
	*/
	philo_eat(philo);
}

void	philo_eat(t_philo	*philo)
{
	if (stop_sim(philo->data))
		return ;
	pthread_mutex_lock(philo->f_left);
	if (stop_sim(philo->data))
	{
		pthread_mutex_unlock(philo->f_right);
		pthread_mutex_unlock(philo->f_left);
		return ;
	}
	time_message(philo, GREEN, FORK);
	//forse altro controllo su stop
	time_message(philo, YELLOW, EAT);
	philo->when_last_meal = whats_the_time();
	if (usleep(philo->data->time_to_eat * 1000) != 0)
		error("	philo failed usleep while eating");
	pthread_mutex_unlock(philo->f_right);
	pthread_mutex_unlock(philo->f_left);
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
