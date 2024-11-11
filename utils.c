/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlucc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:44:06 by scarlucc          #+#    #+#             */
/*   Updated: 2024/11/11 17:00:45 by scarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(char *msg)
{
	printf(RED "Error\n" NO_COLOR);
	printf(YELLOW "%s\n" NO_COLOR, msg);
}

size_t	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}
