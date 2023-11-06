/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaptist <mbaptist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:47:19 by mbaptist          #+#    #+#             */
/*   Updated: 2023/11/06 14:23:04 by mbaptist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo			philos[PHILO_MAX];
	t_table			table;
	pthread_mutex_t	forks[PHILO_MAX];

	if (!validate_args(argc, argv))
		return (close_game("Error: Invalid arguments.", NULL, NULL));
	start_table(&table, philos);
	start_forks(forks, ft_atoi(argv[1]));
	start_philos(philos, &table, forks, argv);
	create_threads(&table, forks);
	close_game(NULL, &table, forks);
	return (0);
}

int	close_game(const char *msg, t_table *table, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (table)
	{
		pthread_mutex_destroy(&table->write_lock);
		pthread_mutex_destroy(&table->dead_lock);
	}
	if (forks)
	{
		while (i < table->philos[0].num_of_philos)
		{
			pthread_mutex_destroy(&forks[i]);
			i++;
		}
	}
	if (msg)
		printf("%s\n", msg);
	return (EXIT_FAILURE);
}
