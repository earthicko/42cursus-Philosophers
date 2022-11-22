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

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000 - info->t_start);
}

int	philo_eat(t_philoinfo *info)
{
	time_t	t_now;

	t_now = get_t_simulation(info->tableinfo);
	printf("%ld %d is eating\n", t_now, info->i + 1);
	(info->tableinfo->philo_t_last_eat)[info->i] = t_now;
	(info->tableinfo->philo_n_eats)[info->i]++;
	usleep(info->tableinfo->time_eat);
	pthread_mutex_unlock(info->forks[0]);
	pthread_mutex_unlock(info->forks[1]);
	return (0);
}

int	philo_sleep(t_philoinfo *info)
{
	printf("%ld %d is sleeping\n",
		get_t_simulation(info->tableinfo), info->i + 1);
	usleep(info->tableinfo->time_slp);
	return (0);
}

void	*philo_start_routine(void *arg)
{
	t_philoinfo		*info;
	int				(*think_routine)(t_philoinfo *);

	info = arg;
	pthread_detach((info->tableinfo->philo_ids)[info->i]);
	printf("Philo %d start TID %p, MID %p | %p\n",
		info->i + 1,
		info->tableinfo->philo_ids + info->i,
		info->forks[0], info->forks[1]);
	if (info->i % 2)
		think_routine = philo_think_odd;
	else
		think_routine = philo_think_even;
	while (1)
	{
		if (think_routine(info))
			return (NULL);
		if (philo_eat(info))
			return (NULL);
		if (philo_sleep(info))
			return (NULL);
	}
	return (NULL);
}
