/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoamzil <yoamzil@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:40:32 by yoamzil           #+#    #+#             */
/*   Updated: 2023/08/14 14:44:36 by yoamzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

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

int	init_philosophers(t_philo *philo, char **argv)
{
	int		i;
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

int	init_data(t_philo *philo, char **argv)
{
	init_philosophers(philo, argv);
	if (philo->num_of_philos < 1 || philo->time_to_die < 0
		|| philo->time_to_eat < 0 || philo->time_to_sleep < 0)
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
