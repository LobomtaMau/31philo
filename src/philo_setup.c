/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaptist <mbaptist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:45:08 by mbaptist          #+#    #+#             */
/*   Updated: 2023/10/27 15:12:50 by mbaptist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void initialize_mutexes(pthread_mutex_t forks[], int num)
{
    int i;
    
    i = 0;
    while (i < num)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
}

void create_philosophers_and_threads(pthread_t philosopher_threads[], t_philosopher philosophers[], 
        pthread_mutex_t forks[], char **argv, int argc, unsigned long simulation_start_time, int *philosopher_died, pthread_mutex_t *death_mutex)
{
    int i;
    
    i = 0;
    while (i < ft_atoi(argv[1]))
    {
        philosophers[i].id = i + 1;
        philosophers[i].time_to_die = ft_atoi(argv[2]);
        philosophers[i].time_to_eat = ft_atoi(argv[3]);
        philosophers[i].time_to_sleep = ft_atoi(argv[4]);
        philosophers[i].number_of_times_to_eat = (argc == 6) ? ft_atoi(argv[5]) : -1;
        philosophers[i].eat_count = 0;
        philosophers[i].left_fork = &forks[i];
        philosophers[i].right_fork = &forks[(i + 1) % ft_atoi(argv[1])];
        philosophers[i].last_eating_time = simulation_start_time;
        philosophers[i].start_time = simulation_start_time;
        philosophers[i].total_philos = ft_atoi(argv[1]);
        philosophers[i].death_flag = philosopher_died;
        philosophers[i].death_mutex = death_mutex;
        pthread_create(&philosopher_threads[i], NULL, philosopher_life, &philosophers[i]);
        i++;
    }
}

void join_threads(pthread_t philosopher_threads[], int num)
{
    int i;
    
    i = 0;
    while (i < num) {
        pthread_join(philosopher_threads[i], NULL);
        i++;
    }
}

void destroy_mutexes(pthread_mutex_t forks[], int num)
{
    int i;
    
    i = 0;
    while (i < num) {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
}

void *philosopher_life(void *data)
{
    t_philosopher *philosopher = (t_philosopher *)data;

    while (1)
	{
        unsigned long current_time;
        unsigned long relative_time;
        
        current_time = get_curr_time_in_milliscs();
        relative_time = current_time - philosopher->start_time;
       
        if (current_time - philosopher->last_eating_time >= philosopher->time_to_die)
        {
        printf(RED "%lu %d died." RESET "\n", relative_time, philosopher->id);
        pthread_mutex_lock(philosopher->death_mutex);
        *(philosopher->death_flag) = 1;
        pthread_mutex_unlock(philosopher->death_mutex);
        return NULL;
        }
        if (philosopher->total_philos == 1) 
        {
            continue;
        }
        pthread_mutex_lock(philosopher->left_fork);
        pthread_mutex_lock(philosopher->right_fork);
        relative_time = get_curr_time_in_milliscs() - philosopher->start_time;
        printf("%lu %d is eating\n", relative_time, philosopher->id);
        philosopher->last_eating_time = get_curr_time_in_milliscs();
        usleep(philosopher->time_to_eat * 1000);
        philosopher->eat_count++;
        pthread_mutex_unlock(philosopher->right_fork);
        pthread_mutex_unlock(philosopher->left_fork);
        if (philosopher->eat_count == philosopher->number_of_times_to_eat)
            break;
        relative_time = get_curr_time_in_milliscs() - philosopher->start_time;
        printf("%lu %d is sleeping\n", relative_time, philosopher->id);
        usleep(philosopher->time_to_sleep * 1000);
        relative_time = get_curr_time_in_milliscs() - philosopher->start_time;
        printf("%lu %d is thinking\n", relative_time, philosopher->id);
        ft_usleep(100);
    }
    return NULL;
}
