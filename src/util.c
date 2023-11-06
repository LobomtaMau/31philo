/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaptist <mbaptist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:59:50 by mbaptist          #+#    #+#             */
/*   Updated: 2023/11/06 14:15:50 by mbaptist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int i;
    long res;

    i = 0;
    res = 0;
    while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '+')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
	{
        res = res * 10 + (str[i] - '0');
        if (res > INT_MAX) return -1; 
        i++;
    }
    return (int)res;
}
int	validate_args(int argc, char **argv)
{
	int	i;
	int value;

	if (argc < 5 || argc > 6)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (!is_valid_arg(argv[i]))
			return (0);
		value = ft_atoi(argv[i]);
		if (value <= 0)
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_arg(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (close_game("Error: getting time.\n", NULL, NULL));
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}
