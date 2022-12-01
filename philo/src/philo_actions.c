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

#include "simulation.h"
#include "philo.h"
#include "timetools.h"
#include <pthread.h>

static void	philo_report_last_eat_time(t_philo *philo)
{
	pthread_mutex_lock(philo->table->lock_infos + philo->i);
	(philo->table->philo_t_last_eat)[philo->i] = (philo->buf).t;
	pthread_mutex_unlock(philo->table->lock_infos + philo->i);
}

static void	philo_report_n_eats(t_philo *philo)
{
	pthread_mutex_lock(philo->table->lock_infos + philo->i);
	(philo->table->philo_n_eats)[philo->i]++;
	pthread_mutex_unlock(philo->table->lock_infos + philo->i);
}

void	philo_eat(t_philo *philo)
{
	philo_push_msg(philo, EATING);
	philo_report_last_eat_time(philo);
	ft_usleep(philo->env->time_eat, philo->table->n_philos / 2);
	pthread_mutex_unlock(philo->forks[0]);
	pthread_mutex_unlock(philo->forks[1]);
	philo_report_n_eats(philo);
}

void	philo_sleep(t_philo *philo)
{
	philo_push_msg(philo, SLEEPING);
	ft_usleep(philo->env->time_slp, philo->table->n_philos / 2);
}

void	philo_think(t_philo *philo)
{
	philo_push_msg(philo, THINKING);
	pthread_mutex_lock(philo->forks[0]);
	philo_push_msg(philo, FORKTAKEN);
	pthread_mutex_lock(philo->forks[1]);
	philo_push_msg(philo, FORKTAKEN);
}
