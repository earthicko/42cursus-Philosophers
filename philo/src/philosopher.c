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

#include "t_info.h"
#include "philo.h"
#include "error_handler.h"
#include "timetools.h"
#include "msg_queue.h"
#include <pthread.h>
#include <stdlib.h>

void	philo_push_msg(t_philo *philo, int msg)
{
	(philo->buf).t = get_t_simulation(philo->env);
	(philo->buf).content = msg;
	if (push_msg_queue(philo->table->queue, &(philo->buf)))
		exit(handle_error("Message queue full."));
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
	while (1)
	{
		if (counter == 0)
			ft_usleep(T_INITIAL_DELAY, philo->table->n_philos / 2);
		else if (counter % 2)
		{
			philo_think(philo);
			philo_eat(philo);
		}
		else
			philo_sleep(philo);
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
		while (1)
		{
			philo_think(philo);
			philo_eat(philo);
			philo_sleep(philo);
		}
	}
	else
	{
		while (1)
		{
			philo_sleep(philo);
			philo_think(philo);
			philo_eat(philo);
		}
	}
}

void	*philo_start_routine(void *arg)
{
	t_philo		*philo;

	philo = arg;
	(philo->buf).i = philo->i + 1;
	pthread_detach((philo->table->philo_ids)[philo->i]);
	if (philo->table->n_philos % 2 == 0)
		philo_strategy_even(philo);
	else
		philo_strategy_odd(philo);
	return (NULL);
}
