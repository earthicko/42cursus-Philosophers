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
# include <pthread.h>

typedef pthread_t		t_thread;
typedef pthread_mutex_t	t_mutex;

typedef struct s_tableinfo
{
	int			n_philos;
	int			time_die;
	int			time_eat;
	int			time_slp;
	int			n_eats_until_done;
	t_thread	*philo_ids;
	int			*philo_n_eats;
	int			*philo_t_last_eat;
	t_mutex		*fork_ids;
}	t_tableinfo;

typedef struct s_philoinfo
{
	t_tableinfo	*tableinfo;
	int			i;
	t_mutex		*forks[2];
}	t_philoinfo;

void	*start_routine(void *arg);
#endif
