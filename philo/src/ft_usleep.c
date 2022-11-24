/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:51:49 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:50 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>

int	ft_usleep(useconds_t microseconds)
{
	struct timeval	start;
	struct timeval	now;
	time_t			elapsed;

	gettimeofday(&start, NULL);
	while (1)
	{
		if (usleep(1))
			return (-1);
		gettimeofday(&now, NULL);
		elapsed = (now.tv_sec - start.tv_sec) * 1000000;
		elapsed += (now.tv_usec - start.tv_usec);
		if (elapsed >= microseconds)
			return (0);
	}
	return (0);
}
