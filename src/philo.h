/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaptist <mbaptist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:06:25 by mbaptist          #+#    #+#             */
/*   Updated: 2023/11/06 13:55:47 by mbaptist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_table
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_table;

//starting
void				start_table(t_table *table, t_philo *philos);
void				start_forks(pthread_mutex_t *forks, int n_philo);
void				start_tertulia(t_philo *philo, char **argv);
void				start_philos(t_philo *philos, t_table *table,
						pthread_mutex_t *forks, char **argv);

//Control
void				*philo_tertulia(void *ptr);
int					create_threads(t_table *table, pthread_mutex_t *forks);
int					search_death(t_philo *philo);
void				*control(void *ptr);
int					check_death(t_philo *philos);
int					dead_philo(t_philo *philo, size_t time_to_die);
int					check_all_eat(t_philo *philos);

//Actions
void				is_eating(t_philo *philo);
void				is_sleeping(t_philo *philo);
void				is_thinking(t_philo *philo);

//Utils
int					ft_atoi(const char *str);
int					is_valid_arg(const char *str);
int					validate_args(int argc, char **argv);
size_t				get_current_time(void);
int					ft_usleep(size_t milliseconds);
void				print_msg(char *str, t_philo *philo, int id);
int					close_game(const char *msg, t_table *table,
						pthread_mutex_t *forks);

#endif
