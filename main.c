/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:21:08 by scarlucc          #+#    #+#             */
/*   Updated: 2024/11/28 17:45:02 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	table;

	if (parsing(argc, argv, 0))
		return (1);
	//2 init data
	if (init_sim(argv ,&table, -1))
		free_all();//da fare
	//3 start program

	//end program
	free(table.philos);
	free(table.forks);
	return (0);
}
