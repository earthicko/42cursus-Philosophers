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
# include "t_info.h"
# include "msg_queue.h"
# include <pthread.h>
# include <sys/time.h>
# define T_PERIOD_LOOP 5000
# define T_INITIAL_DELAY 100

time_t	get_t_simulation(t_tableinfo *info);
void	*philo_start_routine(void *arg);
void	philo_push_msg(t_philoinfo *info, int msg);

void	philo_eat(t_philoinfo *info);
void	philo_sleep(t_philoinfo *info);
void	philo_think(t_philoinfo *info);
#endif
