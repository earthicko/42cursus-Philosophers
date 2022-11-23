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
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

time_t	get_t_simulation(t_tableinfo *info)
{
	struct timeval	t;
	long long		temp;

	gettimeofday(&t, NULL);
	temp = t.tv_sec * 1000;
	temp += t.tv_usec / 1000;
	temp -= info->t_start;
	return (temp);
}

void	*philo_start_routine(void *arg)
{
	t_philoinfo		*info;

	info = arg;
	pthread_detach((info->tableinfo->philo_ids)[info->i]);
	philo_strategy_0(info);
	return (NULL);
}
