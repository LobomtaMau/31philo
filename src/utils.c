/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaptist <mbaptist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:59:50 by mbaptist          #+#    #+#             */
/*   Updated: 2023/10/23 17:13:42 by mbaptist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	else if (str[i] == '+' || str[i] == '-')
		i++;
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

unsigned long get_curr_time_in_milliscs()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return (now.tv_sec * 1000UL) + (now.tv_usec / 1000UL);
}