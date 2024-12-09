/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:19:41 by scarlucc          #+#    #+#             */
/*   Updated: 2024/12/09 09:28:59 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_message(t_philo	*philo, const char	*color, const char	*message)
{
	int	timestamp;

	pthread_mutex_lock(&philo->data->msg);
	timestamp = whats_the_time() - philo->data->prog_start;
	if (timestamp < 0)
	{
		pthread_mutex_unlock(&philo->data->msg);
		return (error("	time_message failed because gettimeofday failed"), 1);
	}
	pthread_mutex_lock(&philo->data->stop_mtx);
	if (!philo->data->stop || !ft_strncmp(message, DIED, 5))
	{
		printf("%s%i %i %s%s", color, timestamp, philo->p_id, message,
			NO_COLOR);
		pthread_mutex_unlock(&philo->data->stop_mtx);
		return (pthread_mutex_unlock(&philo->data->msg), 0);
	}
	pthread_mutex_unlock(&philo->data->stop_mtx);
	return (pthread_mutex_unlock(&philo->data->msg), 1);
}

void	cleanup(t_data *table)
{
	int	count;

	count = -1;
	if (pthread_mutex_destroy(&table->stop_mtx) != 0)
		error("	failed to destroy stop_mtx");
	if (pthread_mutex_destroy(&table->msg) != 0)
		error("	failed to destroy msg");
	while (++count < table->p_total)
	{
		if (pthread_mutex_destroy(&table->philos[count].meal_mtx) != 0)
			error("	failed to destroy meal_mtx in cleanup");
	}
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
