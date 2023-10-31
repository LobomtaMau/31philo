/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaptist <mbaptist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:45:08 by mbaptist          #+#    #+#             */
/*   Updated: 2023/10/31 16:01:43 by mbaptist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void is_sleeping(t_philo *philo)
{
    print_msg("is sleeping", philo, philo->id);
    ft_usleep(philo->time_to_sleep);
}

void is_eating(t_philo *philo)
{
    pthread_mutex_lock(philo->r_fork);
    print_msg("has taken a fork", philo, philo->id);
    if(philo->num_of_philos == 1)
    {
        ft_usleep(philo->time_to_die);
        pthread_mutex_unlock(philo->r_fork);
        return;
    }
    pthread_mutex_lock(philo->l_fork);
    print_msg("has taken a fork", philo, philo->id);
    philo->eating = 1;
    print_msg("is eating", philo, philo->id);
    pthread_mutex_lock(philo->meal_lock);
    philo->last_meal = get_current_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->meal_lock);
    ft_usleep(philo->time_to_eat);
    philo->eating = 0;
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
}

void is_thinking(t_philo *philo)
{
    print_msg("is thinking", philo, philo->id);
}

void print_msg(char *str, t_philo *philo, int id)
{
    size_t time;
    pthread_mutex_lock(philo->write_lock);
    time = get_current_time() - philo->start_time;
    if(!search_death(philo))
        printf("%zu %d %s\n", time, id, str);
    pthread_mutex_unlock(philo->write_lock);
}

int check_all_eat(t_philo *philos)
{
    int i;
    int all_eaten;

    i = 0;
    all_eaten = 1;
    if (philos[0].num_times_to_eat <= 0)
        return (0);
    while (i < philos[0].num_of_philos && all_eaten)
    {
        pthread_mutex_lock(philos[i].meal_lock);
        if (philos[i].meals_eaten < philos[i].num_times_to_eat)
            all_eaten = 0;
        pthread_mutex_unlock(philos[i].meal_lock);
        i++;
    }
    if(all_eaten)
    {
        pthread_mutex_lock(philos[0].dead_lock);
        *philos->dead = 1;
        pthread_mutex_unlock(philos[0].dead_lock);
        return (1);
    }
    return (0);
}