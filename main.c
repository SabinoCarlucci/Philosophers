/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:21:08 by scarlucc          #+#    #+#             */
/*   Updated: 2024/12/04 17:36:28 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	table;
	int		count;

	if (parsing(argc, argv, 0))
		return (1);
	if (init_sim(argv, &table, -1))
		cleanup(&table);
	count = -1;
	while (++count < table.p_total)
	{
		if (pthread_create(&table.philos[count].thread, NULL, &start_dinner,
				&table.philos[count]) != 0)
			return (error("	philo creation failed"), cleanup(&table), 1);
	}
	dead_or_full(&table, -1, 1);
	count = -1;
	while (++count < table.p_total)
	{
		if (pthread_join(table.philos[count].thread, NULL) != 0)
			error("	thread join failed");
	}
	cleanup(&table);
	return (0);
}
