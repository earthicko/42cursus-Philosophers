/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_think.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:51:22 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:23 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	philo_think_odd(t_philoinfo *info)
{
	printf("%ld %d is thinking\n",
		get_t_simulation(info->tableinfo), info->i + 1);
	pthread_mutex_lock(info->forks[0]);
	printf("%ld %d has taken a fork\n",
		get_t_simulation(info->tableinfo), info->i + 1);
	pthread_mutex_lock(info->forks[1]);
	printf("%ld %d has taken a fork\n",
		get_t_simulation(info->tableinfo), info->i + 1);
	return (0);
}

int	philo_think_even(t_philoinfo *info)
{
	time_t	t_now;

	t_now = get_t_simulation(info->tableinfo);
	printf("%ld %d is thinking\n", t_now, info->i + 1);
	pthread_mutex_lock(info->forks[1]);
	printf("%ld %d has taken a fork\n",
		get_t_simulation(info->tableinfo), info->i + 1);
	pthread_mutex_lock(info->forks[0]);
	printf("%ld %d has taken a fork\n",
		get_t_simulation(info->tableinfo), info->i + 1);
	return (0);
}
