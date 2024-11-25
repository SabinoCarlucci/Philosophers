/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:21:08 by scarlucc          #+#    #+#             */
/*   Updated: 2024/11/25 19:17:34 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philos;
	t_fork	*forks;

	if (parsing(argc, argv, 0))
		return (1);
	//2 init data
	philos = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philos)
		error("malloc philos failed");
	forks = malloc(sizeof(t_fork) * ft_atoi(argv[1]));
	if (!forks)
		error("malloc forks failed");
	if (!philos || !forks)//unico return per fallimento malloc di tutto, forse devo cambiare 
		return (1);

	//3 start program

	//end program
	free(philos);
	free(forks);
	return (0);
}
