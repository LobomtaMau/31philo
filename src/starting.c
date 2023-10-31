/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaptist <mbaptist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:59:50 by mbaptist          #+#    #+#             */
/*   Updated: 2023/10/31 16:03:09 by mbaptist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void start_table(t_table *table, t_philo *philos)
{
    table->dead_flag = 0;
    table->philos = philos;
    pthread_mutex_init(&table->write_lock, NULL);
    pthread_mutex_init(&table->dead_lock , NULL);
    pthread_mutex_init(&table->meal_lock, NULL);
}

void start_forks(pthread_mutex_t *forks, int n_philo)
{
    int i;

    i = 0;
    while (i < n_philo)
    {
        pthread_mutex_init(&forks[i], NULL);
		i++;
    }
}

void start_philos(t_philo *philos, t_table *table, pthread_mutex_t *forks, char **argv)
{
    int i;

    i = 0;
    while (i < ft_atoi(argv[1]))
    {
        philos[i].id = i + 1;
        philos[i].eating = 0;
        philos[i].meals_eaten = 0;
		start_tertulia(&philos[i], argv);
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].write_lock = &table->write_lock;
		philos[i].dead_lock = &table->dead_lock;
		philos[i].meal_lock = &table->meal_lock;
		philos[i].dead = &table->dead_flag;
		philos[i].l_fork = &forks[i];
        if (i == 0)
            philos[i].r_fork = &forks[philos[i].num_of_philos - 1];
        else
            philos[i].r_fork = &forks[i - 1];
        i++;
    }
}

void start_tertulia(t_philo * philo, char **argv)
{
    philo->num_of_philos = ft_atoi(argv[1]);
    philo->time_to_eat = ft_atoi(argv[3]);
    philo->time_to_sleep = ft_atoi(argv[4]);
    philo->time_to_die = ft_atoi(argv[2]);
    if(argv[5])
        philo->num_times_to_eat = ft_atoi(argv[5]);
    else
        philo->num_times_to_eat = -1;
}

int search_death(t_philo *philo)
{
    pthread_mutex_lock(philo->dead_lock);
    if (*philo->dead == 1)
        return (pthread_mutex_unlock(philo->dead_lock), 1);
    pthread_mutex_unlock(philo->dead_lock);
    return (0);
}

