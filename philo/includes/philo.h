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
# include "msg_queue.h"
# include <pthread.h>
# include <sys/time.h>
# define T_PERIOD_LOOP 5000
# define T_INITIAL_DELAY 100

typedef pthread_t		t_thread;
typedef pthread_mutex_t	t_mutex;

typedef struct s_tableinfo
{
	int			n_philos;
	time_t		time_die;
	time_t		time_eat;
	time_t		time_slp;
	int			n_eats_until_done;
	t_thread	*philo_ids;
	int			*philo_n_eats;
	time_t		*philo_t_last_eat;
	t_mutex		*fork_ids;
	time_t		t_start;
	t_msg_queue	*queue;
}	t_tableinfo;

typedef struct s_philoinfo
{
	t_msg		buf;
	t_tableinfo	*tableinfo;
	int			i;
	t_mutex		*forks[2];
}	t_philoinfo;

time_t	get_t_simulation(t_tableinfo *info);
void	*philo_start_routine(void *arg);
void	philo_push_msg(t_philoinfo *info, int msg);

void	philo_strategy_0(t_philoinfo *info);
void	philo_strategy_1(t_philoinfo *info);
void	philo_strategy_2(t_philoinfo *info);
#endif
