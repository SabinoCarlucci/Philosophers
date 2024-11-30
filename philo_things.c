/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_things.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:33:57 by scarlucc          #+#    #+#             */
/*   Updated: 2024/11/30 19:39:18 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo	*philo)
{
	int	timestamp;

	timestamp = whats_the_time() - philo->data->prog_start;
	printf(MAGENTA "%i %i %s" NO_COLOR, timestamp, philo->p_id, THINK);
}

void	philo_eat(void)
{
	
}

void	philo_sleep(void)
{
	
}

void	start_routine(void *point)
{
	t_philo	*philo;

	philo = (t_philo *)point;
	//sistema per dare un tempo ai filosofi
	while (1)
	{
		philo_think(philo);
		//dovrei mettere eat e sleep, ma non basta che sia think a chiamare le altre due?
	}
}
