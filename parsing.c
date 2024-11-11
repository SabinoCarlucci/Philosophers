/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:20:54 by scarlucc          #+#    #+#             */
/*   Updated: 2024/11/11 16:50:30 by scarlucc         ###   ########.fr       */
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
		{
			error(ERR_NUM);
			return (1);
		}
		count++;
	}
	return (0);
}

int	check_limits(char *arg, char *compare)
{
	int	count;

	count = 0;
	while (arg[count])
	{
		if (arg[count] > compare[count])
		{
			error(ERR_LIMIT);
			return (1);
		}
		count++;
	}
	return (0);
}

int	parsing(char **argv)
{
	int		n_input;
	char	*compare;

	n_input = 0;
	while (argv[++n_input])
	{
		if (is_num(argv[n_input]))
			return (1);
		if (n_input == 1 || n_input == 5)
			compare = INT;
		else
			compare = LONG;
		if (ft_strlen(argv[n_input]) > ft_strlen(compare))
		{
			error(ERR_LIMIT);
			return (1);
		}
		else if (ft_strlen(argv[n_input]) == ft_strlen(compare))
			check_limits(argv[n_input], compare);
	}
	return (0);
}
