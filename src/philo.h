/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaptist <mbaptist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:38:37 by mbaptist          #+#    #+#             */
/*   Updated: 2023/10/27 15:13:16 by mbaptist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define RED "\x1B[31m"
#define RESET "\x1B[0m"

typedef struct s_philosopher
{
    int total_philos;
    int id;
    int *death_flag;

    unsigned long time_to_die;
    unsigned long time_to_sleep;
    
    unsigned long time_to_eat;
    unsigned long last_eating_time;
    unsigned long start_time;
    
    int number_of_times_to_eat;
    int eat_count;
    
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *death_mutex;
    
} t_philosopher;

//philo
void *philosopher_life(void *data);
int close_game(const char *msg);

//threads
void destroy_mutexes(pthread_mutex_t forks[], int num);
void join_threads(pthread_t philosopher_threads[], int num);
void create_philosophers_and_threads(pthread_t philosopher_threads[], t_philosopher philosophers[], pthread_mutex_t forks[], char **argv, int argc, unsigned long simulation_start_time, int *philosopher_died, pthread_mutex_t *death_mutex);
void initialize_mutexes(pthread_mutex_t forks[], int num);

//utils
int	ft_atoi(const char *str);
unsigned long get_curr_time_in_milliscs(void);
int	ft_usleep(unsigned long milliseconds);


#endif