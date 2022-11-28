/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:51:22 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:23 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_info.h"
#include "philo.h"
#include "timetools.h"
#include <pthread.h>

void	philo_eat(t_philoinfo *info)
{
	philo_push_msg(info, EATING);
	(info->tableinfo->philo_t_last_eat)[info->i] = (info->buf).t;
	ft_usleep(info->tableinfo->time_eat, info->tableinfo->n_philos / 2);
	pthread_mutex_unlock(info->forks[0]);
	pthread_mutex_unlock(info->forks[1]);
	(info->tableinfo->philo_n_eats)[info->i]++;
}

void	philo_sleep(t_philoinfo *info)
{
	philo_push_msg(info, SLEEPING);
	ft_usleep(info->tableinfo->time_slp, info->tableinfo->n_philos / 2);
}

void	philo_think(t_philoinfo *info)
{
	philo_push_msg(info, THINKING);
	pthread_mutex_lock(info->forks[0]);
	philo_push_msg(info, FORKTAKEN);
	pthread_mutex_lock(info->forks[1]);
	philo_push_msg(info, FORKTAKEN);
}
