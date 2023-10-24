/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaptist <mbaptist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:47:19 by mbaptist          #+#    #+#             */
/*   Updated: 2023/10/24 17:19:03 by mbaptist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    unsigned long simulation_start_time;
    
    if (argc < 5 || argc > 6)
        return close_game("Error: Not enough arguments.");
    int number_of_philosophers = ft_atoi(argv[1]);
    if (!number_of_philosophers)
        return close_game("Error: Failed to create philosophers.");
    
    int philosopher_died = 0; //decl
    pthread_mutex_t death_mutex;
    pthread_mutex_t forks[number_of_philosophers];
    initialize_mutexes(forks, number_of_philosophers);
    pthread_t philosopher_threads[number_of_philosophers];
    t_philosopher philosophers[number_of_philosophers];
    
    simulation_start_time = get_curr_time_in_milliscs();
    create_philosophers_and_threads(philosopher_threads, philosophers, forks, argv, argc, simulation_start_time, &philosopher_died, &death_mutex);
    join_threads(philosopher_threads, number_of_philosophers);
    destroy_mutexes(forks, number_of_philosophers);
    pthread_mutex_destroy(&death_mutex);

    return 0;
}
int close_game(const char *msg)
{
    printf("%s\n", msg);
    return EXIT_FAILURE;
}
