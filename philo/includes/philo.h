/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:51:49 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:50 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "simulation.h"
# include <sys/time.h>
# define T_INITIAL_DELAY 100

void	*philo_start_routine(void *arg);
int		philo_push_msg(t_philo *philo, int msg);

void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
#endif
