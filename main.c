/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:21:08 by scarlucc          #+#    #+#             */
/*   Updated: 2024/11/11 16:59:54 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (parsing(argv))
			return (1);
		//2 init data

		//3 start program

		//end program
		return (0);
	}
	else
		error(ERR_USAGE);
	return (0);
}
