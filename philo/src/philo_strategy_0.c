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

// strategy suitable for even number of philos
// philo with n % 2 == 1 will pick fork on their left then right,
// n % 2 == 0 vise versa.
// philo with n % 2 == 1 will also start picking forks a little later
// to allow n % 2 == 0 to have meal first.
void	philo_strategy_0(t_philoinfo *info)
{
	if (info->i % 2)
		usleep(T_INITIAL_DELAY);
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
