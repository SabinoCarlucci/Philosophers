/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:20:54 by scarlucc          #+#    #+#             */
/*   Updated: 2024/11/11 15:20:59 by scarlucc         ###   ########.fr       */
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
			error("input non numerico\0");//qui mettici un define
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
		if (arg[count] >= compare[count])
		{
			error("Input beyond limit");
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
			error("troppe cifre in input\0");//define per il tipo di errore
			return (1);
		}
		else if (ft_strlen(argv[n_input]) == ft_strlen(compare))
			check_limits(argv[n_input], compare);
	}
	return (0);
}
