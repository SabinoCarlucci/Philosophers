/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:20:54 by scarlucc          #+#    #+#             */
/*   Updated: 2024/11/25 19:14:44 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Usage:  ./philo 5 800 200 200 [5]

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

int	check_limits(char *arg, char *high_compare, int low_compare)
{
	int	count;

	count = -1;
	if (ft_strlen(arg) > ft_strlen(high_compare))
		return (error(ERR_LIMIT), 1);
	else if (ft_strlen(arg) == ft_strlen(high_compare))
	{
		while (arg[++count])
		{
			if (arg[count] > high_compare[count])
				return (error(ERR_LIMIT), 1);
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
			if (check_limits(argv[n_input], LIM_PHILO, 0))
				return (1);
		}
		else if (n_input == 5)
		{
			if (check_limits(argv[n_input], INT, 0))
				return (1);
		}
		else
		{
			if (check_limits(argv[n_input], INT, LIM_TIME))
				return (1);
		}
	}
	return (0);
}
