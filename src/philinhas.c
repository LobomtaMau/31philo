#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct
{
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_to_eat;
	int				eat_count;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct timeval	last_eat;
}					t_philosopher;

long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void	*philosopher_life(void *data)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)data;
	while (1)
	{
		// Try to get forks
		pthread_mutex_lock(philosopher->left_fork);
		pthread_mutex_lock(philosopher->right_fork);
		// Eat
		printf("%ld %d is eating\n", get_timestamp(), philosopher->id);
		philosopher->eat_count++;
		usleep(philosopher->time_to_eat * 1000);
		gettimeofday(&philosopher->last_eat, NULL);
		pthread_mutex_unlock(philosopher->right_fork);
		pthread_mutex_unlock(philosopher->left_fork);
		if (philosopher->eat_count == philosopher->number_of_times_to_eat)
			break ;
		// Sleep
		printf("%ld %d is sleeping\n", get_timestamp(), philosopher->id);
		usleep(philosopher->time_to_sleep * 1000);
		// Think
		printf("%ld %d is thinking\n", get_timestamp(), philosopher->id);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	if (argc < 5)
	{
		printf("Error: Not enough arguments.\n");
		return (1);
	}

	int number_of_philosophers = atoi(argv[1]);
	int time_to_die = atoi(argv[2]);
	int time_to_eat = atoi(argv[3]);
	int time_to_sleep = atoi(argv[4]);
	int number_of_times_each_philosopher_must_eat = (argc == 6) ? atoi(argv[5]) :
		-1;

	pthread_mutex_t forks[number_of_philosophers];
	for (int i = 0; i < number_of_philosophers; i++)
	{
		pthread_mutex_init(&forks[i], NULL);
	}

	pthread_t philosopher_threads[number_of_philosophers];
	t_philosopher philosophers[number_of_philosophers];

	for (int i = 0; i < number_of_philosophers; i++)
	{
		philosophers[i].id = i + 1;
		philosophers[i].time_to_die = time_to_die;
		philosophers[i].time_to_eat = time_to_eat;
		philosophers[i].time_to_sleep = time_to_sleep;
		philosophers[i].number_of_times_to_eat = number_of_times_each_philosopher_must_eat;
		philosophers[i].eat_count = 0;
		philosophers[i].left_fork = &forks[i];
		philosophers[i].right_fork = &forks[(i + 1) % number_of_philosophers];
		pthread_create(&philosopher_threads[i], NULL, philosopher_life,
				&philosophers[i]);
	}

	for (int i = 0; i < number_of_philosophers; i++)
	{
		pthread_join(philosopher_threads[i], NULL);
	}

	for (int i = 0; i < number_of_philosophers; i++)
	{
		pthread_mutex_destroy(&forks[i]);
	}
	return (0);
}