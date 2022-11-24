/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_strategy_1.c                                 :+:      :+:    :+:   */
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

// strategy suitable for odd number of philos
// each philo will add a small delay every Nth cycle of their lives.
// philo n will start adding their delay from nth cycle.
// every philo will pick their forks from left to right.
// if counter is at 0, add delay.
// else if counter is even, sleep.
// else, eat.
void	philo_strategy_1(t_philoinfo *info)
{
	int	counter;

	counter = info->i;
	while (1)
	{
		if (counter == 0)
			usleep(T_INITIAL_DELAY);
		else if (counter % 2)
		{
			philo_think(info);
			philo_eat(info);
		}
		else
			philo_sleep(info);
		counter = (counter + 1) % info->tableinfo->n_philos;
	}
}
