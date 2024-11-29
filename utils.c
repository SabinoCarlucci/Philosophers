/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:19:41 by scarlucc          #+#    #+#             */
/*   Updated: 2024/11/29 17:20:41 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_and_destroy(t_data *table, t_mtx *forks, int count)
{
	while (++count < table->p_total)
	{
		if (pthread_mutex_destroy(&forks[count]) != 0)
			error("	failed to destroy forks");
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
