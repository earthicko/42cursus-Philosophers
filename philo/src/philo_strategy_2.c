/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_strategy_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:51:22 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:23 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "msg_queue.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

static void	philo_eat(t_philoinfo *info)
{
	philo_push_msg(info, EATING);
	(info->tableinfo->philo_t_last_eat)[info->i] = (info->buf).t;
	(info->tableinfo->philo_n_eats)[info->i]++;
	usleep(info->tableinfo->time_eat);
	pthread_mutex_unlock(info->forks[0]);
	pthread_mutex_unlock(info->forks[1]);
}

static void	philo_sleep(t_philoinfo *info)
{
	philo_push_msg(info, SLEEPING);
	usleep(info->tableinfo->time_slp);
}

static void	philo_think(t_philoinfo *info)
{
	philo_push_msg(info, THINKING);
	pthread_mutex_lock(info->forks[0]);
	philo_push_msg(info, FORKTAKEN);
	pthread_mutex_lock(info->forks[1]);
	philo_push_msg(info, FORKTAKEN);
}

// strategy suitable for even number of philos
// philo with n % 2 == 1 will think, eat and sleep.
// philo with n % 2 == 0 will sleep, think and eat.
void	philo_strategy_2(t_philoinfo *info)
{
	if (info->i % 2)
	{
		while (1)
		{
			philo_think(info);
			philo_eat(info);
			philo_sleep(info);
		}
	}
	else
	{
		while (1)
		{
			philo_sleep(info);
			philo_think(info);
			philo_eat(info);
		}
	}
}
