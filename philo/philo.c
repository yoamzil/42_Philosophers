/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoamzil <yoamzil@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 01:36:27 by yoamzil           #+#    #+#             */
/*   Updated: 2023/08/10 12:38:11 by yoamzil          ###   ########.fr       */
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
int init_mutex(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->num_of_philos)
	{
		if (pthread_mutex_init(&philo->forks[i], NULL) != 0)
		{
			perror("Error: Failed to initialize mutex");
			return 1;
		}
		i++;
	}printf("hello\n");
	i = 0;
	while (i < philo->num_of_philos)
	{
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % philo->num_of_philos;
		i++;
	}

	return 0;
}

int init_philosophers(t_philo *philo)
{
	int i;

	i = philo->num_of_philos;
	while (i > 0)
	{
		philo[i].id = i;
		pthread_mutex_init(&philo[i].mutex, NULL);
		// printf("khrej\n");
		// exit (0);
		i--;
	}
	return (0);
}

int allocation(t_philo *philo)
{
	
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->num_of_philos);
	if (!philo->forks)
	{
		// free(data->thread_id);
		return (1);
	}
	philo->data = malloc(sizeof(t_data));
	if (!philo->data)
		return (1);
	
	philo->thread_id = malloc(sizeof(pthread_t*) * philo->num_of_philos);
	if (!philo->thread_id)
		return (1);

	printf("khedama\n");
	
	return (0);
}
int init_data(t_philo *philo, char **argv)
{
	
	
	if (allocation(philo))
		return (1);
	
	philo->data->time_to_die = ft_atoi(argv[2]);
	philo->data->time_to_eat = ft_atoi(argv[3]);
	philo->data->time_to_sleep = ft_atoi(argv[4]);
	philo->data->full = 0;
	philo->data->died = 0;
	if (philo->num_of_philos < 1 || philo->data->time_to_die < 0 || philo->data->time_to_eat < 0 || philo->data->time_to_sleep < 0)
		return (1);
	if (argv[5])
	{
		philo->data->must_eat = ft_atoi(argv[5]);
		if (philo->data->must_eat <= 0)
			return (1);
	}
	else
		philo->data->must_eat = -1;
	
	if (init_mutex(philo))
		return (1);
	printf("hi\n");
	init_philosophers(philo);
	return (0);
}

#include <sys/time.h>

long long timestamp(void)
{
	struct timeval t;
	gettimeofday(&t, NULL);

	long long sec_to_ms = (long long)t.tv_sec * 1000;
	long long usec_to_ms = (long long)t.tv_usec / 1000;

	return sec_to_ms + usec_to_ms;
}

void eating(t_philo *philo)
{
	t_data *data;
	
	data = philo->data;

	// Lock the left fork
	pthread_mutex_lock(&(philo->forks[philo->left_fork]));
	printf("has taken a fork");
	// action_print(data, philo->id, "has taken a fork");

	// Lock the right fork
	// pthread_mutex_lock(&(data->forks[philo->right_fork]));
	// action_print(data, philo->id, "has taken a fork");

	// // Lock the meal check mutex to prevent race conditions
	// pthread_mutex_lock(&(data->meal_check));
	// action_print(data, philo->id, "is eating");

	// // Update the philosopher's last meal timestamp
	// philo->t_last_meal = timestamp();

	// // Unlock the meal check mutex to allow other philosophers to eat
	// pthread_mutex_unlock(&(data->meal_check));

	// // Simulate eating by sleeping for a specific duration (time_to_eat)
	// smart_sleep(data->time_to_eat, data);

	// // Increment the number of times the philosopher has eaten
	// (philo->num_of_meals)++;

	// // Unlock both forks after eating
	// pthread_mutex_unlock(&(data->forks[philo->left_fork]));
	// pthread_mutex_unlock(&(data->forks[philo->right_fork]));
}

void *routine(void *void_philo)
{
	int i;
	t_philo *philo;
	// t_data *data;

	i = 0;
	philo = (t_philo *)void_philo;
	// data = philo->data;
	// printf("dkhel\n");
	// exit (1);
	// if (philo->id % 2)
	// 	usleep(15000);
	while (philo->data->died == 0)
	{
		printf("dkhel\n");
		exit (0);
		eating(philo);

		if (philo->data->full)
			break;
	}
	// (void)void_philo;
	// printf("philo %d: left fork: %d, right fork: %d\n", philo->id, philo->left_fork, philo->right_fork);
	return NULL;
}
int starting_thread(t_philo *philo)
{
	int i = 0;
	// t_philo *philo = data->philo;
	// pthread_t thread_id;

	philo->data->first_timestamp = timestamp();
	// printf("first_timestamp: %lu\n", data->first_timestamp);
	while (i < philo->num_of_philos)
	{
		if (pthread_create(&philo->thread_id[i], NULL, routine, NULL))
			return 1;

		philo->data->current_timestamp = timestamp();
		i++;
		// printf("khrej\n");
		// printf("current_timestamp: %lu\n", data->current_timestamp);
	}

	// death_checker(data);
	// exit_launcher(data);

	return 0;
}

int main(int argc, char **argv)
{
	// t_data data;
	t_philo	*philo;
	int	variable;

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
	philo = malloc(sizeof(t_philo) * variable);
	if (!philo)
		return (1);
	philo->num_of_philos = variable;
	if (init_data(philo, argv))
	{
		printf("Error: Wrong arguments\n");
		return (1);
	}
	// if (starting_thread(philo))
		// return (1);
}
