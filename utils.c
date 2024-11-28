/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*            +                                    +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:44:06 by scarlucc          #+#    #+#             */
/*   Updated: 2024/11/11 17:00:45 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	whats_the_time()
{
	struct timeval tv;

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
