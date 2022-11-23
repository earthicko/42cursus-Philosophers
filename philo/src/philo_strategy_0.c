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
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

static void	philo_eat(t_philoinfo *info)
{
	time_t	t_now;

	t_now = get_t_simulation(info->tableinfo);
	printf("%ld %d is eating\n", t_now, info->i + 1);
	(info->tableinfo->philo_t_last_eat)[info->i] = t_now;
	(info->tableinfo->philo_n_eats)[info->i]++;
	usleep(info->tableinfo->time_eat);
	pthread_mutex_unlock(info->forks[0]);
	pthread_mutex_unlock(info->forks[1]);
}

static void	philo_sleep(t_philoinfo *info)
{
	printf("%ld %d is sleeping\n",
		get_t_simulation(info->tableinfo), info->i + 1);
	usleep(info->tableinfo->time_slp);
}

static void	philo_think_odd(t_philoinfo *info)
{
	printf("%ld %d is thinking\n",
		get_t_simulation(info->tableinfo), info->i + 1);
	pthread_mutex_lock(info->forks[0]);
	printf("%ld %d has taken a fork\n",
		get_t_simulation(info->tableinfo), info->i + 1);
	pthread_mutex_lock(info->forks[1]);
	printf("%ld %d has taken a fork\n",
		get_t_simulation(info->tableinfo), info->i + 1);
}

static void	philo_think_even(t_philoinfo *info)
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
}

void	philo_strategy_0(t_philoinfo *info)
{
	if (info->i % 2)
		usleep(1);
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
