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

#include "simulation.h"
#include "philo.h"
#include "error_handler.h"
#include "timetools.h"
#include "msg_queue.h"
#include <pthread.h>
#include <stdlib.h>

int	philo_keep_going(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(philo->table->lock_infos + philo->i);
	ret = (philo->table->terminate)[philo->i];
	pthread_mutex_unlock(philo->table->lock_infos + philo->i);
	return (!ret);
}

int	philo_push_msg(t_philo *philo, int msg)
{
	(philo->buf).t = get_t_simulation(philo->env);
	(philo->buf).content = msg;
	if (push_msg_queue(philo->table->queue, &(philo->buf)) < 0)
	{
		handle_error("Message queue full.");
		return (-1);
	}
	return (0);
}

// strategy suitable for odd number of philos
// each philo will add a small delay every Nth cycle of their lives.
// philo n will start adding their delay from nth cycle.
// every philo will pick their forks from left to right.
// if counter is at 0, add delay.
// else if counter is even, sleep.
// else, eat.
void	philo_strategy_odd(t_philo *philo)
{
	int	counter;

	counter = philo->i;
	while (philo_keep_going(philo))
	{
		if (counter == 0)
			ft_usleep(T_INITIAL_DELAY, philo->table->n_philos / 2);
		else if (counter % 2)
		{
			if (philo_think(philo) || philo_eat(philo))
				return ;
		}
		else
		{
			if (philo_sleep(philo))
				return ;
		}
		counter = (counter + 1) % philo->table->n_philos;
	}
}

// strategy suitable for even number of philos
// philo with n % 2 == 1 will think, eat and sleep.
// philo with n % 2 == 0 will sleep, think and eat.
void	philo_strategy_even(t_philo *philo)
{
	if (philo->i % 2)
	{
		while (philo_keep_going(philo))
		{
			if (philo_sleep(philo) || philo_think(philo) || philo_eat(philo))
				return ;
		}
	}
	else
	{
		while (philo_keep_going(philo))
		{
			if (philo_think(philo) || philo_eat(philo) || philo_sleep(philo))
				return ;
		}
	}
}

void	*philo_start_routine(void *arg)
{
	t_philo		*philo;

	philo = arg;
	(philo->buf).i = philo->i + 1;
	if (philo->table->n_philos == 1 || philo->table->n_philos % 2 == 0)
		philo_strategy_even(philo);
	else
		philo_strategy_odd(philo);
	return (NULL);
}
