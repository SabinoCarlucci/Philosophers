/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:19:41 by scarlucc          #+#    #+#             */
/*   Updated: 2024/12/03 17:57:25 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	time_message(t_philo	*philo, const char	*color, const char	*message)
{
	int	timestamp;
	
	pthread_mutex_lock(&philo->data->start_mtx);//forse salvezza
	timestamp = whats_the_time() - philo->data->prog_start;
	pthread_mutex_unlock(&philo->data->start_mtx);
	if (timestamp < 0)
		error("	time_message failed because gettimeofday failed");
	else
		printf("%s%i %i %s%s", color, timestamp, philo->p_id, message, NO_COLOR);
}

void	cleanup(t_data *table)
{
	int	count;

	count = -1;
	if (pthread_mutex_destroy(&table->stop_mtx) != 0)
			error("	failed to destroy stop_mtx");
	free(table->forks);
	free(table->philos);
}

int	whats_the_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (error(ERR_GETTIME), -1);
	else
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

size_t	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

int	ft_atoi(const char *nptr)
{
	int	out;
	int	sign;
	int	i;

	sign = 1;
	out = 0;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		out = (out * 10) + (nptr[i] - '0');
		i++;
	}
	return (out * sign);
}
