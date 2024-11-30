/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:21:08 by scarlucc          #+#    #+#             */
/*   Updated: 2024/11/30 20:01:33 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	table;
	int		count;

	if (parsing(argc, argv, 0))
		return (1);
	//2 init data
	if (init_sim(argv ,&table, -1))
		free_and_destroy(&table, table.forks, -1);
	//3 start program
	count = -1;
	while (++count < table.p_total)
	{
		if (pthread_create(&table.philos[count].thread, NULL, &start_routine,
				&table.philos[count]) != 0)
		{
			error("	philo creation failed");
			return (free_and_destroy(&table, table.forks, -1), 1);
		}
	}
	start_prog(&table, -1);
	//end program
	free_and_destroy(&table, table.forks, -1);
	return (0);
}
