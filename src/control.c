/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaptist <mbaptist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:45:08 by mbaptist          #+#    #+#             */
/*   Updated: 2023/10/31 16:03:26 by mbaptist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int dead_philo(t_philo *philo, size_t time_to_die)
{
    pthread_mutex_lock(philo->meal_lock);
    if(get_current_time() - philo->last_meal >= time_to_die && philo->eating == 0)
        return (pthread_mutex_unlock(philo->meal_lock), 1);
    pthread_mutex_unlock(philo->meal_lock);
    return (0); 
}

int check_death(t_philo *philos)
{
    int i;

    i = 0;
    while (i < philos[0].num_of_philos)
    {
        if (dead_philo(&philos[i], philos[i].time_to_die))
        {
            print_msg("died", &philos[i], philos[i].id);
            pthread_mutex_lock(philos[0].dead_lock);
            *philos->dead = 1;
            pthread_mutex_unlock(philos[0].dead_lock);
            return (1);
        }
        i++;
    }
    return (0);
}

void *control(void *ptr)
{
    t_philo *philos;
    
    philos = (t_philo *)ptr;
    while (1)
        if(check_death(philos) == 1 || check_all_eat(philos) == 1)
            break;
    return (ptr);
}

void *philo_tertulia(void *ptr)
{
    t_philo *philo;
    
    philo = (t_philo *) ptr;
    if (philo->id % 2 == 0)
        ft_usleep(1);
    while (!search_death(philo))
    {
        is_eating(philo);
        is_sleeping(philo);
        is_thinking(philo);
    }
    return (ptr);
}

int create_threads(t_table *table, pthread_mutex_t *forks)
{
    pthread_t the_death;
    int i;

    if(pthread_create(&the_death, NULL, &control, table->philos) != 0)
		close_game("Thread creation error", table, forks);
    i = 0;
    while (i < table->philos[0].num_of_philos)
    {
        if (pthread_create(&table->philos[i].thread, NULL, &philo_tertulia, &table->philos[i]) != 0)
            close_game("Error: failed to create threads", table, forks);
        i++;
    }
    i = 0;
    if (pthread_join(the_death, NULL) != 0)
        close_game("Error: Join threads fail", table, forks);
    while(i < table->philos[0].num_of_philos)
    {
        if(pthread_join(table->philos[i].thread, NULL) != 0)
            close_game("Error: Join threads fail", table, forks);
        i++;
    }
    return (0);
}
