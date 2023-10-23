/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaptist <mbaptist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:38:37 by mbaptist          #+#    #+#             */
/*   Updated: 2023/10/23 11:05:09 by mbaptist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct s_philo
{
    pthread_t   thread;
    int id;
    int eating;
    int meals_ate;
    size_t start_time;
    size_t last_meal;
    size_t time_to_die;
    size_t time_to_eat;
    size_t time_to_sleep;
    int nr_philos;
    int nr_times_to_eat;
    int *dead;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *write_lock;
    pthread_mutex_t *dead_lock;
    pthread_mutex_t *meal_lock;
}   t_philo;

typedef struct s_program
{
    int dead_flag;
    pthread_mutex_t write_lock;
    pthread_mutex_t dead_lock;
    pthread_mutex_t meal_lock;
    t_philo *philos;
}   t_program;