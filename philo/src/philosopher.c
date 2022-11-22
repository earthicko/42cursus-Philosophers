/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:51:22 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:23 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	eat(void)
{
	return (0);
}

int	sleep(void)
{
	return (0);
}

int	think(void)
{
	return (0);
}

void	*start_routine(void *arg)
{
	t_philoinfo	*info;

	info = arg;
	printf("Philo %d start ", info->i);
	printf("TID %p, ", info->tableinfo->philo_ids + info->i);
	printf("MID %p | %p\n", info->forks[0], info->forks[1]);
	while (1)
	{
		if (eat())
			return (NULL);
		if (sleep())
			return (NULL);
		if (think())
			return (NULL);
	}
	return (arg);
}
