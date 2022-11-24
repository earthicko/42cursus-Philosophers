/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timetools.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:51:49 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:50 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMETOOLS_H
# define TIMETOOLS_H
# include "philo.h"
# include <unistd.h>

int		ft_usleep(useconds_t microseconds);
time_t	get_t_simulation(t_tableinfo *info);
#endif
