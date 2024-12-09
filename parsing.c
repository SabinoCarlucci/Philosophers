/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:20:54 by scarlucc          #+#    #+#             */
/*   Updated: 2024/12/09 09:48:40 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(const char *msg)
{
	write(2, RED, ft_strlen(RED));
	write(2, "Error:\n", 7);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	write(2, NO_COLOR, ft_strlen(NO_COLOR));
}

int	is_num(char *arg)
{
	int	count;

	count = 0;
	while (arg[count])
	{
		if (arg[count] < '0' || arg[count] > '9')
			return (error(ERR_NUM), 1);
		count++;
	}
	return (0);
}

int	check_limits(char *arg, char *high_compare, int low_compare, int count)
{
	if (ft_strlen(arg) > ft_strlen(high_compare))
		return (error(ERR_LIMIT), 1);
	else if (ft_strlen(arg) == ft_strlen(high_compare))
	{
		if (!ft_strncmp(high_compare, LIM_PHILO, ft_strlen(LIM_PHILO)))
		{
			if (ft_atoi(arg) > ft_atoi(high_compare))
				return (error(ERR_LIMIT), 1);
		}
		else
		{
			while (arg[++count])
			{
				if (arg[count] > high_compare[count])
					return (error(ERR_LIMIT), 1);
			}
		}
	}
	else
	{
		if (ft_atoi(arg) <= low_compare)
			return (error(ERR_LIMIT_LOW), 1);
	}
	return (0);
}

int	parsing(int argc, char **argv, int n_input)
{
	if (argc < 5 || argc > 6)
		return (error(ERR_IN_NUM), 1);
	while (argv[++n_input])
	{
		if (is_num(argv[n_input]))
			return (1);
		if (n_input == 1)
		{
			if (check_limits(argv[n_input], LIM_PHILO, 0, -1))
				return (1);
		}
		else if (n_input == 5)
		{
			if (check_limits(argv[n_input], INT, 0, -1))
				return (1);
		}
		else
		{
			if (check_limits(argv[n_input], INT, LIM_TIME, -1))
				return (1);
		}
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0') && i < (n - 1))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
