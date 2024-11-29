/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:21:08 by scarlucc          #+#    #+#             */
/*   Updated: 2024/11/29 17:24:11 by scarlucc         ###   ########.fr       */
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
		free_and_destroy(&table, table.forks, -1);
	//3 start program

	//end program
	free_and_destroy(&table, table.forks, -1);
	return (0);
}
