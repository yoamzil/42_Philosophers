/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoamzil <yoamzil@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 01:36:27 by yoamzil           #+#    #+#             */
/*   Updated: 2023/08/14 11:16:07 by yoamzil          ###   ########.fr       */
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

	i = -1;
	while (++i < philo->num_of_philos)
		pthread_mutex_init(&forks[i], NULL);
	i = 0;
	while (i < philo->num_of_philos)
	{
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % philo->num_of_philos];
		i++;
	}
	pthread_mutex_init(&philo[0].m1, NULL);
	pthread_mutex_init(&philo[0].m2, NULL);
	return (0);
}

long timestamp(void)
{
	struct timeval t;
	long time;

	gettimeofday(&t, NULL);
	time = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (time);
}

void ft_usleep(useconds_t time)
{
	long start;

	start = timestamp();
	while ((timestamp() - start) < time)
		usleep(50);
}
int init_philosophers(t_philo *philo, char **argv)
{
	int i;
	long	time;

	time = timestamp();
	i = 0;
	while (i < philo->num_of_philos)
	{
		philo[i].first_timestamp = time;
		philo[i].last_meal = time;
		philo[i].id = i + 1;
		philo[i].num_of_meals = 0;
		philo[i].ate = 0;
		philo[i].died = 0;
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		i++;
	}
	return (0);
}

int init_data(t_philo *philo, char **argv)
{
	init_philosophers(philo, argv);
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
	return (0);
}

void printing(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->m2);
	printf("%ld %d %s\n", timestamp() - philo->first_timestamp, philo->id, str);
	pthread_mutex_unlock(&philo->m2);
}
int	death_checker(t_philo *philo, int ac)
{
	int i;

	i = 0;
	// (void)ac;
	while (1)
	{
		// printf("ac: %d  num of meals: %d   last arg: %d\n", ac, philo[i].num_of_meals, philo->must_eat);
		// exit (0);
		pthread_mutex_lock(&philo[i].m1);
		if (ac == 6 && philo[i].num_of_meals > philo[i].must_eat)
			return (0);
		if ((timestamp() - philo[i].last_meal) >= philo[i].time_to_die)
		{
			pthread_mutex_lock(&philo[i].m2);
			philo[i].died = 1;
			pthread_mutex_unlock(&philo[i].m2);
			printf("%ld %d %s\n", timestamp() - philo[i].first_timestamp, philo[i].id, "died");
			// exit (0);
			return (0);
		}
		pthread_mutex_unlock(&philo[i].m1);
		// printf("num of meals: %d\n", philo[i].num_of_meals);
		// i++;
		// if (i == philo->num_of_philos)
		// 	i = 0;
	}
	return (1);
}

void eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printing(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	printing(philo, "has taken a fork");
	printing(philo, "is eating");
	pthread_mutex_lock(&philo->m1);
	philo->num_of_meals++;
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&philo->m1);
	ft_usleep(philo->time_to_eat);
	// pthread_mutex_lock(&philo->m1);
	// pthread_mutex_unlock(&philo->m1);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
void *routine(void *void_philo)
{
	t_philo *philo;
	philo = (t_philo *)void_philo;
	if (philo->id % 2 == 0)
		ft_usleep(200);
	pthread_mutex_lock(&philo->m2);
	int d = philo->died;
	pthread_mutex_unlock(&philo->m2);
	while (!d)
	{
		pthread_mutex_lock(&philo->m2);
		d = philo->died;
		pthread_mutex_unlock(&philo->m2);
		printing(philo, "is thinking");
		eating(philo);
		printing(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep);
	}
	// pthread_mutex_unlock(&philo->m2);
	return NULL;
}
int starting_thread(pthread_t *threads, t_philo *philo, int ac)
{
	int i = 0;
	while (i < philo->num_of_philos)
	{
		if (pthread_create(&threads[i], NULL, routine, &philo[i]))
		{
			printf("Failed creating threads\n");
			return 1;
		}
		i++;
	}
	if(!death_checker(philo, ac))
		return (0);
	i = 0;
	while (i < philo->num_of_philos)
	{
		if (pthread_join(threads[i], NULL))
			return 1;
		i++;
	}
		printf("hmaaa\n");
		exit (0);
	// exit_launcher(data);

	return 0;
}
// int	threads_join(pthread_t *threads, t_philo *philo)
// {
// 	int i;

// 	i = 0;
// 	while (i < philo->num_of_philos)
// 	{
// 		if (pthread_join(threads[i++], NULL))
// 			return 1;
// 	}
// 	return 0;
// }


int main(int argc, char **argv)
{
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
	philo = malloc(sizeof(t_philo) * variable);
	threads = malloc(sizeof(pthread_t) * variable);
	forks = malloc(sizeof(pthread_mutex_t) * variable);

	if (!philo || !threads || !forks)
		return (1);
	philo->num_of_philos = variable;
	
	if (init_data(philo, argv) || init_mutex(philo, forks))
	{
		printf("Error: Wrong arguments\n");
		return (1);
	}
	starting_thread(threads, philo, argc);
	
	// threads_join(threads, philo);
}
