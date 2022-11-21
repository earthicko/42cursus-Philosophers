/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:51:40 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:41 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATOR_H
# define ALLOCATOR_H
# include "philo.h"

int	free_tableinfo(t_tableinfo *tableinfo);
int	alloc_tableinfo(t_tableinfo *tableinfo);
int	alloc_philoinfos(t_philoinfo **philoinfos, t_tableinfo *tableinfo);
int	alloc_infos(t_tableinfo *tableinfo, t_philoinfo **philoinfos);
#endif
