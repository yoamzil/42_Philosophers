/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoamzil <yoamzil@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 01:36:27 by yoamzil           #+#    #+#             */
/*   Updated: 2023/08/11 22:53:56 by yoamzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_atoi(const char *str)
{
	int i;
	int number;
	int sign;

	i = 0;
	number = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i + 1] == '+' || str[i + 1] == '-')
			return (0);
		else if (str[i] == '-')
			sign *= (-1);
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	return (number * sign);
}

int checker(char **argv)
{
	int i;
	int j;
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] != ' ' && (argv[i][j] < '0' || argv[i][j] > '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
int init_mutex(t_philo *philo, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	while (i < philo->num_of_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			perror("Error: Failed to initialize mutex");
			return 1;
		}
		i++;
	}
	i = 0;
	while (i < philo->num_of_philos)
	{
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % philo->num_of_philos];
		i++;
	}

	return 0;
}

long timestamp(void)
{
	struct timeval t;
	gettimeofday(&t, NULL);

	long sec_to_ms = (long)t.tv_sec * 1000;
	long usec_to_ms = (long)t.tv_usec / 1000;

	return (sec_to_ms + usec_to_ms);
}
int init_philosophers(t_philo *philo)
{
	int i;
	long	time;

	time = timestamp();
	i = 0;
	while (i < philo->num_of_philos)
	{
		philo[i].first_timestamp = time;
		philo[i].id = i + 1;
		philo[i].time_left = philo->time_to_die;
		philo[i].num_of_meals = 0;
		philo[i].ate = 0;
		pthread_mutex_init(&philo[i].m1, NULL);
		// printf("khrej\n");
		// exit (0);
		i++;
	}
	return (0);
}

int allocation(t_philo *philo)
{
	
	philo->data = malloc(sizeof(t_data));
	if (!philo->data)
		return (1);
	return (0);
}
int init_data(t_philo *philo, char **argv)
{
	if (allocation(philo))
		return (1);
	
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->full = 0;
	philo->died = 0;
	if (philo->num_of_philos < 1 || philo->time_to_die < 0 || philo->time_to_eat < 0 || philo->time_to_sleep < 0)
		return (1);
	if (argv[5])
	{
		philo->must_eat = ft_atoi(argv[5]);
		if (philo->must_eat <= 0)
			return (1);
	}
	else
		philo->must_eat = -1;
	init_philosophers(philo);
	return (0);
}

int ft_usleep(long long time)
{
	long start;
	long elapsed_time;

	start = timestamp();
	elapsed_time = 0;
	while (elapsed_time < time)
	{
		usleep(1000);
		elapsed_time = timestamp() - start;
	}
	return 0;
}

// void eating(t_philo *philo)
// {
// 	// printf("dkhel\n");
// 	// 
// 	// Lock the left fork
// 	pthread_mutex_lock(philo->right_fork);
// 	pthread_mutex_lock(&philo->m1);
// 	printf("%d has taken a fork\n", philo->id);
// 	pthread_mutex_unlock(&philo->m1);

// 	// Lock the right fork
// 	pthread_mutex_lock(philo->left_fork);
// 	pthread_mutex_lock(&philo->m1);
// 	printf("%d has taken a fork\n", philo->id);
// 	pthread_mutex_unlock(&philo->m1);

// 	philo->ate = 1;
// 	philo->time_left = timestamp() + philo->data->time_to_die;

// 	// // Update the philosopher's last meal timestamp
// 	philo->last_meal = timestamp();
// 	pthread_mutex_lock(&philo->m1);
// 	printf("%lld %d is eating\n", timestamp() - philo->data->first_timestamp, philo->id);
// 	pthread_mutex_unlock(&philo->m1);

// 	// // Unlock the meal check mutex to allow other philosophers to eat
// 	// pthread_mutex_unlock(&(data->meal_check));

// 	// // Simulate eating by sleeping for a specific duration (time_to_eat)
// 	// smart_sleep(data->time_to_eat, data);

// 	// // Increment the number of times the philosopher has eaten
// 	(philo->num_of_meals)++;
// 	ft_usleep(philo->data->time_to_eat);

// 	// // Unlock both forks after eating
// 	pthread_mutex_unlock(philo->right_fork);
// 	pthread_mutex_unlock(philo->left_fork);
// }

void printing(t_philo philo, char *str)
{
	pthread_mutex_lock(&philo.m1);
	// printf("first time: %ld\n", philo.first_timestamp);
	// printf("current time: %ld\n", timestamp());
	printf("%ld %d %s\n", timestamp() - philo.first_timestamp, philo.id, str);
	pthread_mutex_unlock(&philo.m1);
}

void eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	printing(*philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	printing(*philo, "has taken a fork");
	printing(*philo, "is eating");
	pthread_mutex_lock(&philo->m1);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&philo->m1);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(&philo->m1);
	philo->num_of_meals++;
	pthread_mutex_unlock(&philo->m1);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	// exit(0);
}
void *routine(void *void_philo)
{
	t_philo *philo;
	philo = (t_philo *)void_philo;
	printf("thread: %d created\n", philo->id);
	// if (philo->id % 2 == 0)
	// 	ft_usleep(1);
	while (1)
	{
		// printing(*philo, "is thinking");
		printf("philo: %d is thinking\n", philo->id);
		eating(philo);
		// printing(*philo, "is sleeping");
		printf("philo: %d is sleeping\n", philo->id);
		ft_usleep(philo->time_to_sleep);
	}
	// return void_philo;
}
int starting_thread(pthread_t *threads, t_philo *philo)
{
	int i = 0;
	// t_philo *philo = data->philo;
	// pthread_t thread_id;

	printf("startint threads\n");
	// printf("first_timestamp: %lu\n", data->first_timestamp);
	while (i < philo->num_of_philos)
	{
		if (pthread_create(&threads[i], NULL, routine, &philo[i]))
		{
			return 1;
		}
		i++;
		// printf("current_timestamp: %lu\n", data->current_timestamp);
	}
	
	
	// death_checker(data);
	// exit_launcher(data);

	return 0;
}
int	threads_join(pthread_t *threads, t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->num_of_philos)
	{
		if (pthread_join(threads[i++], NULL))
			return 1;
	}
	return 0;
}


int main(int argc, char **argv)
{
	// t_data data;
	pthread_t *threads;
	pthread_mutex_t *forks;
	t_philo	*philo;
	int variable;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	if (checker(argv))
	{
		printf("Error: Wrong arguments\n");
		return (1);
	}
	variable = ft_atoi(argv[1]);
	// printf("nb: %d\n", variable);
	philo = malloc(sizeof(t_philo) * variable);
	threads = malloc(sizeof(pthread_t) * variable);
	forks = malloc(sizeof(pthread_mutex_t) * variable);

	if (!philo || !threads || !forks)
		return (1);
	philo->num_of_philos = variable;
	
	printf("first time: %ld\n", philo->first_timestamp);
	// exit (0);
	if (init_data(philo, argv) || init_mutex(philo, forks))
	{
		printf("Error: Wrong arguments\n");
		return (1);
	}
	if (starting_thread(threads, philo))
		return (1);
	if (threads_join(threads, philo))
		return 1;
}
