/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timetools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:51:49 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:50 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_info.h"
#include "timetools.h"
#include <unistd.h>
#include <sys/time.h>

int	ft_usleep(useconds_t microseconds, suseconds_t check_period)
{
	struct timeval	start;
	struct timeval	now;
	time_t			elapsed;

	gettimeofday(&start, NULL);
	while (1)
	{
		if (usleep(check_period))
			return (-1);
		gettimeofday(&now, NULL);
		elapsed = (now.tv_sec - start.tv_sec) * 1000000;
		elapsed += (now.tv_usec - start.tv_usec);
		if (elapsed >= (time_t) microseconds)
			return (0);
	}
	return (0);
}

time_t	get_t_simulation(t_tableinfo *info)
{
	struct timeval	t;
	time_t			temp;

	gettimeofday(&t, NULL);
	temp = t.tv_sec * 1000000;
	temp += t.tv_usec;
	temp -= info->t_start;
	return (temp);
}
