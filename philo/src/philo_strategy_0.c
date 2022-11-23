/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_strategy_0.c                                 :+:      :+:    :+:   */
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
	(info->tableinfo->philo_t_last_eat_ms)[info->i] = (info->buf).t_ms;
	(info->tableinfo->philo_n_eats)[info->i]++;
	usleep(info->tableinfo->time_eat_us);
	pthread_mutex_unlock(info->forks[0]);
	pthread_mutex_unlock(info->forks[1]);
}

static void	philo_sleep(t_philoinfo *info)
{
	philo_push_msg(info, SLEEPING);
	usleep(info->tableinfo->time_slp_us);
}

static void	philo_think_odd(t_philoinfo *info)
{
	philo_push_msg(info, THINKING);
	pthread_mutex_lock(info->forks[0]);
	philo_push_msg(info, FORKTAKEN);
	pthread_mutex_lock(info->forks[1]);
	philo_push_msg(info, FORKTAKEN);
}

static void	philo_think_even(t_philoinfo *info)
{
	philo_push_msg(info, THINKING);
	pthread_mutex_lock(info->forks[1]);
	philo_push_msg(info, FORKTAKEN);
	pthread_mutex_lock(info->forks[0]);
	philo_push_msg(info, FORKTAKEN);
}

void	philo_strategy_0(t_philoinfo *info)
{
	if (info->i % 2)
		usleep(T_INITIAL_DELAY_US);
	while (1)
	{
		if (info->i % 2)
			philo_think_odd(info);
		else
			philo_think_even(info);
		philo_eat(info);
		philo_sleep(info);
	}
}
