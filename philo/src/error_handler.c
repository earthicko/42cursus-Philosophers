/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:51:13 by donghyle          #+#    #+#             */
/*   Updated: 2022/11/21 21:51:14 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handler.h"
#include <stdio.h>

int	handle_error(char *error_msg)
{
	printf("%s\n", error_msg);
	return (CODE_ERROR);
}
