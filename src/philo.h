/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaptist <mbaptist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:38:37 by mbaptist          #+#    #+#             */
/*   Updated: 2023/10/23 17:13:14 by mbaptist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philosopher
{
    int id;
    unsigned long time_to_die;
    unsigned long time_to_eat;
    unsigned long time_to_sleep;
    int number_of_times_to_eat;
    int eat_count;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    unsigned long last_eating_time;
} t_philosopher;

//philo
void *philosopher_life(void *data);
int close_game(const char *msg);

//threads
void destroy_mutexes(pthread_mutex_t forks[], int num);
void join_threads(pthread_t philosopher_threads[], int num);
void create_philosophers_and_threads(pthread_t philosopher_threads[], t_philosopher philosophers[], pthread_mutex_t forks[], char **argv, int argc);
void initialize_mutexes(pthread_mutex_t forks[], int num);

//utils
int	ft_atoi(const char *str);
unsigned long get_curr_time_in_milliscs();

#endif

// typedef struct s_philo
// {
//     pthread_t   thread;
//     int id;
//     int eating;
//     int meals_ate;
//     size_t start_time;
//     size_t last_meal;
//     size_t time_to_die;
//     size_t time_to_eat;
//     size_t time_to_sleep;
//     int nr_philos;
//     int nr_times_to_eat;
//     int *dead;
//     pthread_mutex_t *right_fork;
//     pthread_mutex_t *left_fork;
//     pthread_mutex_t *write_lock;
//     pthread_mutex_t *dead_lock;
//     pthread_mutex_t *meal_lock;
// }   t_philo;

// typedef struct s_program
// {
//     int dead_flag;
//     pthread_mutex_t write_lock;
//     pthread_mutex_t dead_lock;
//     pthread_mutex_t meal_lock;
//     t_philo *philos;
// }   t_program;

